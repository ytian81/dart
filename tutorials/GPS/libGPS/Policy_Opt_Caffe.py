import os
os.environ['GLOG_minloglevel']='2'
import numpy as np
import caffe
import copy
from caffe.proto.caffe_pb2 import SolverParameter,TRAIN, TEST
from google.protobuf.text_format import MessageToString
from NNBuilder import NNConstructor
from Policy_Caffe import CaffePolicy
from file2numpy import file2numpy
import tempfile
import json
import os

class PolicyOptCaffe():
    def __init__(self, x_dim, u_dim, T, N, mPhi):
        """
        x_dim:
        u_dim:
        T:     time horizon of one episode (normally T-1, since no control at the very end step)
        N:     used in pretrain method. 
               pretrain is called after ReadX, ReadU and ReadQuu_inv. Therefore the total number of data pairs is self.T * N
               now N is the number of batches per epoch. Considering caffe_iterations is 50, so the total epochs should be 50/N
        mPhi:  used in finetrain method.
               mPhi is the total number of samples in optimizing Phi
        batch_size: change from 25 to T-1
        """
        caffe.set_mode_cpu()
        self.batch_size = T
        self.x_dim = x_dim
        self.u_dim = u_dim
        self.T     = T
        self.N     = N
        self.mPhi  = mPhi
        self.hidden_dim = 50
        self.caffe_iterations = 5000
        self.caffe_finetune_iterations = 20
        
        self.init_solver()
        self.init_solver2()
        self.init_solver3()
        self.var = 0.1 * np.eye(self.u_dim) # here 0.1 is the parameter set arbitrarily. It would be a better idea to bundle all parameter in a separate file.

        with tempfile.NamedTemporaryFile(delete=False) as _init_f:
            _init_f.write(str(NNConstructor(self.x_dim,self.u_dim,self.hidden_dim,1,TEST)))
        _init_mNet = caffe.Net(_init_f.name, TEST)
        self.policy = CaffePolicy(_init_mNet, self.var)

        self.policyRepo = []

# --------------------------------------------------
# initialize solvers
# --------------------------------------------------
    def init_solver(self):
        solver_param = SolverParameter()
        solver_param.display = 0  # Don't display anything.
        solver_param.base_lr = 0.001
        solver_param.lr_policy = 'fixed'
        solver_param.momentum = 0.9
        solver_param.weight_decay = 0.005
        solver_param.type = 'SGD'
        solver_param.random_seed = 1
         
        solver_param.train_net_param.CopyFrom(NNConstructor(self.x_dim,self.u_dim,self.hidden_dim,self.batch_size,TRAIN))
        
        with open('/tmp/NeuralNetworks.prototxt','w') as f:
            f.write(MessageToString(solver_param))
        
        self.solver=caffe.get_solver(f.name)

    def init_solver2(self):
        solver_param2 = SolverParameter()
        solver_param2.display = 0  # Don't display anything.
        solver_param2.base_lr = 1e-6
        solver_param2.lr_policy = 'fixed'
        solver_param2.momentum = 0.95
        solver_param2.weight_decay = 0.001
        solver_param2.type = 'SGD'
        solver_param2.random_seed = 1
         
        solver_param2.train_net_param.CopyFrom(NNConstructor(self.x_dim,self.u_dim,self.hidden_dim,self.T,"ISLOSS",mPhi=self.mPhi))
            
        with open('/tmp/NeuralNetworks2.prototxt','w') as f:
            f.write(MessageToString(solver_param2))
        
        self.solver2=caffe.get_solver(f.name)

    def init_solver3(self):
        solver_param3 = SolverParameter()
        solver_param3.display = 0  # Don't display anything.
        solver_param3.base_lr = 1e-6
        solver_param3.lr_policy = 'fixed'
        solver_param3.momentum = 0.95
        solver_param3.weight_decay = 0.001
        solver_param3.type = 'SGD'
        solver_param3.random_seed = 1
         
        solver_param3.train_net_param.CopyFrom(NNConstructor(self.x_dim,self.u_dim,self.hidden_dim,self.T,"ISLOSS",mPhi=self.mPhi))
            
        with open('/tmp/NeuralNetworks3.prototxt','w') as f:
            f.write(MessageToString(solver_param3))
        
        self.solver3=caffe.get_solver(f.name)

# --------------------------------------------------
# pretrain neural networks
# --------------------------------------------------
    def pretrain(self):
    # def pretrain(self""", itr, inner_itr"""):
        # Normalize obs, but only compute normalzation at the beginning.
        """
        No normalization right now
        if itr == 0 and inner_itr == 1:
            # 1e-3 to avoid infs if some state dimensions don't change in the
            # first batch of samples
            self.policy.scale = np.diag(1.0 / np.maximum(np.std(self.x, axis=0),
                                                         1e-3))
            self.policy.bias = -np.mean(self.x.dot(self.policy.scale), axis=0)
        obs = obs.dot(self.policy.scale) + self.policy.bias
        """
        print '---------------------------------------------------------'
        print '------------- Pretrain the neural networks --------------'
        print '---------------------------------------------------------'
            
        blob_names = self.solver.net.blobs.keys()
        
        # Assuming that N*T >= self.batch_size.
        batches_per_epoch = np.floor(self.N*self.T / self.batch_size)
        idx = range(self.N*self.T)
        # np.random.shuffle(idx)
        for i in range(self.caffe_iterations):
            # for loop can finish self.caffe_iterations/self.N epoches
            # Load in data for this batch.
            start_idx = int(i * self.batch_size %
                            (batches_per_epoch * self.batch_size))
            idx_i = idx[start_idx:start_idx+self.batch_size]
            self.solver.net.blobs[blob_names[0]].data[:] = self.x[idx_i]
            self.solver.net.blobs[blob_names[1]].data[:] = self.u[idx_i]
            self.solver.net.blobs[blob_names[2]].data[:] = np.linalg.inv(self.var)
        
            self.solver.step(1)
        
            # To get the training loss:
            train_loss = self.solver.net.blobs[blob_names[-1]].data
            if i%500 == 0:
                print train_loss
        
        self.policycopyfromsolver()
        self.solver2copyfromsolver()
        self.solver3copyfromsolver2()
        
        # why this line impacts finetune???
        self.appendpolicyRepo(self.solver.net)

    def ReadX(self):
        self.x = file2numpy('X.numpyout')
        # print self.x

    def ReadU(self):
        # Supposing u_dim is 1, s.t. each row is an instance
        self.u = file2numpy('U.numpyout')
        # print self.u

    def ReadQuu_inv(self):
        # Supposing u_dim is 1, s.t. each row is an instance
        self.Quu_inv = file2numpy('Quu_inv.numpyout')
        self.Quu_inv = np.reshape(self.Quu_inv,(-1,self.u_dim,self.u_dim))
        # print self.Quu_inv

# --------------------------------------------------
# fine tune Neural Network
# --------------------------------------------------
    def finetune(self):
        # need to call setWr() before calling finetune
        
        print '*********************************************************'
        print '************* Finetune the neural networks **************'
        print '*********************************************************'
        
        blob_names = self.solver2.net.blobs.keys()
        for i in range(self.caffe_finetune_iterations):
            print str(i)+' th iteration of finetune'
            self.solver2.net.blobs[blob_names[0]].data[:]=self.samplesets_x
            self.solver2.net.blobs[blob_names[1]].data[:]=self.samplesets_x
            self.solver2.net.blobs[blob_names[2]].data[:]=self.samplesets_u
            self.solver2.net.blobs[blob_names[3]].data[:]=np.linalg.inv(self.var)
            self.solver2.net.blobs[blob_names[4]].data[:]=self.samplesets_Logq
            self.solver2.net.blobs[blob_names[5]].data[:]=self.wr
            
            # params_names = self.solver2.net.params.keys()
            # a = copy.deepcopy(self.solver2.net.params[params_names[0]][0].data)
            # params_names = self.solver3.net.params.keys()
            # b = copy.deepcopy(self.solver3.net.params[params_names[0]][0].data)
            # d = copy.deepcopy(self.solver.net.params[params_names[0]][0].data)

            self.solver2.step(1)
            # To get the training loss:
            train_loss = self.solver2.net.blobs[blob_names[-1]].data
            print train_loss

            # params_names = self.solver2.net.params.keys()
            # c = copy.deepcopy(self.solver2.net.params[params_names[0]][0].data)
            # params_names = self.solver3.net.params.keys()
            # e = copy.deepcopy(self.solver3.net.params[params_names[0]][0].data)
        
        # although fine tuned parameter may not be accepted, it should be kept in self.policyRepo to eval Logq
        self.appendpolicyRepo(self.solver2.net)

    def ReadSampleSets_X(self):
        self.samplesets_x = file2numpy('SampleSets_X.numpyout')
        # print self.samplesets_x

    def ReadSampleSets_U(self):
        # Supposing u_dim is 1, s.t. each row is an instance
        self.samplesets_u = file2numpy('SampleSets_U.numpyout')
        # print self.samplesets_u

    def ReadSampleSets_Quu_inv(self):
        # Supposing u_dim is 1, s.t. each row is an instance
        self.samplesets_Quu_inv = file2numpy('SampleSets_Quu_inv.numpyout')
        self.samplesets_Quu_inv = np.reshape(self.samplesets_Quu_inv,(-1,self.u_dim,self.u_dim))
        # print self.samplesets_Quu_inv

    def ReadSampleSets_Logq(self):
        self.samplesets_Logq = file2numpy('SampleSets_Logq.numpyout')
        # print self.samplesets_Logq

    def setWr(self, _wr=1e-2):
        print 'Setting wr as ',_wr
        self.wr = _wr

    def increaseWr(self):
        if self.wr*10<=1e-2 and self.wr*10>=1e-6:
            print 'Increasing wr from ',self.wr,' to ',self.wr*10
            self.wr = self.wr*10
        else:
            print 'Change of wr is out of bound, thus no change of wr...'
            print 'wr is ',self.wr

    def decreaseWr(self):
        if self.wr*0.1<=1e-2 and self.wr*0.1>=1e-6:
            print 'Decreasing wr from ',self.wr,' to ',self.wr*0.1
            self.wr = self.wr*0.1
        else:
            print 'Change of wr is out of bound, thus no change of wr...'
            print 'wr is ',self.wr

# --------------------------------------------------
# compute loss value without regularizer
# --------------------------------------------------
    def trainnet2forward(self, previous):
        # need to call setWr() before calling finetune
        
        print '*********************************************************'
        print '******** train net2 forward and loss value **************'
        print '*********************************************************'
        if not previous:
            blob_names = self.solver2.net.blobs.keys()
            self.solver2.net.blobs[blob_names[0]].data[:]=self.samplesets_x
            self.solver2.net.blobs[blob_names[1]].data[:]=self.samplesets_x
            self.solver2.net.blobs[blob_names[2]].data[:]=self.samplesets_u
            self.solver2.net.blobs[blob_names[3]].data[:]=np.linalg.inv(self.var)
            self.solver2.net.blobs[blob_names[4]].data[:]=self.samplesets_Logq
            self.solver2.net.blobs[blob_names[5]].data[:]=self.wr

            self.solver2.net.forward()
            self.lossvalue_wo = self.solver2.net.layers[-1].lossvalue_wo
        else:
            blob_names = self.solver3.net.blobs.keys()
            self.solver3.net.blobs[blob_names[0]].data[:]=self.samplesets_x
            self.solver3.net.blobs[blob_names[1]].data[:]=self.samplesets_x
            self.solver3.net.blobs[blob_names[2]].data[:]=self.samplesets_u
            self.solver3.net.blobs[blob_names[3]].data[:]=np.linalg.inv(self.var)
            self.solver3.net.blobs[blob_names[4]].data[:]=self.samplesets_Logq
            self.solver3.net.blobs[blob_names[5]].data[:]=self.wr

            self.solver3.net.forward()
            self.lossvalue_wo = self.solver3.net.layers[-1].lossvalue_wo


    def modifymPhi(self, newmPhi):
        data_layer_info = json.dumps({
            'shape': [{'dim': (newmPhi*self.batch_size, self.x_dim)},
                      {'dim': (newmPhi*self.batch_size, self.x_dim)},
                      {'dim': (newmPhi*self.batch_size, self.u_dim)},
                      {'dim': (newmPhi*self.batch_size, self.u_dim, self.u_dim)},
                      {'dim': (newmPhi*self.batch_size, 1)},
                      {'dim': (1, 1)}
                      ]})
        
        self.solver2.net.layers[-1].mPhi = newmPhi
        self.solver2.net.layers[0].param_str = data_layer_info
        self.solver2.net.reshape()
        
        self.solver3.net.layers[-1].mPhi = newmPhi
        self.solver3.net.layers[0].param_str = data_layer_info
        self.solver3.net.reshape()

    def restoremPhi(self):
        data_layer_info = json.dumps({
            'shape': [{'dim': (self.mPhi*self.batch_size, self.x_dim)},
                      {'dim': (self.mPhi*self.batch_size, self.x_dim)},
                      {'dim': (self.mPhi*self.batch_size, self.u_dim)},
                      {'dim': (self.mPhi*self.batch_size, self.u_dim, self.u_dim)},
                      {'dim': (self.mPhi*self.batch_size, 1)},
                      {'dim': (1, 1)}
                      ]})
        self.solver2.net.layers[-1].mPhi = self.mPhi
        self.solver2.net.layers[0].param_str = data_layer_info
        self.solver2.net.reshape()
        
        self.solver3.net.layers[-1].mPhi = self.mPhi
        self.solver3.net.layers[0].param_str = data_layer_info
        self.solver3.net.reshape()

# --------------------------------------------------
# append one net to self.policyRepo
# --------------------------------------------------
    def appendpolicyRepo(self, _net):
        # first generate one net
        with tempfile.NamedTemporaryFile(delete=False) as f:
            f.write(str(NNConstructor(self.x_dim,self.u_dim,self.hidden_dim,1,TEST)))
        filename = '/tmp/_net.caffemodel'
        _net.save(filename)
        mNet = caffe.Net(f.name, filename, TEST)
        self.policyRepo.append(CaffePolicy(mNet, self.var))


# --------------------------------------------------
# copy or share neural nets
# --------------------------------------------------
    def policycopyfromsolver3(self):
        # ------------------------
        # solver3.net => policy
        # ------------------------
        
        filename='/tmp/Solver3TrainNet.caffemodel'
        self.solver3.net.save(filename)
        self.policy.net.copy_from(filename)

    def policycopyfromsolver2(self):
        # ------------------------
        # solver2.net => policy
        # ------------------------
        
        filename='/tmp/Solver2TrainNet.caffemodel'
        self.solver2.net.save(filename)
        self.policy.net.copy_from(filename)

    def policycopyfromsolver(self):
        # ------------------------
        # solver.net => policy
        # ------------------------
        
        filename='/tmp/SolverTrainNet.caffemodel'
        self.solver.net.save(filename)
        self.policy.net.copy_from(filename)

    def solver2copyfromsolver(self):
        # ------------------------
        # solver.net => solver2.net
        # ------------------------
        
        filename='/tmp/SolverTrainNet.caffemodel'
        self.solver.net.save(filename)
        self.solver2.net.copy_from(filename)
        # self.solver2.net.share_with(self.solver.net)

    def solver3copyfromsolver2(self):
        # ------------------------
        # solver2.net =>solver3.net
        # ------------------------

        filename='/tmp/Solver2TrainNet.caffemodel'
        self.solver2.net.save(filename)
        self.solver3.net.copy_from(filename)

    def solver2copyfromsolver3(self):
        # ------------------------
        # solver3.net =>solver2.net
        # ------------------------

        filename='/tmp/Solver2TrainNet.caffemodel'
        self.solver3.net.save(filename)
        self.solver2.net.copy_from(filename)

# --------------------------------------------------
# logistical function
# --------------------------------------------------
    def setFoo(self):
        self.policy.foo = 100

    def printFoo(self):
        print "~~~~~~~~~~~~~~~~~~~~~ Train Net Parameters ~~~~~~~~~~~~~~~~~~~~~"
        params_names = self.solver.net.params.keys()
        print params_names
        print self.solver.net.params[params_names[0]][0].data[0:3,:]
        print "~~~~~~~~~~~~~~~~~~~~~ Policy Net Parameters ~~~~~~~~~~~~~~~~~~~~~"
        params_names = self.policy.net.params.keys()
        print params_names
        print self.policy.net.params[params_names[0]][0].data[0:3,:]

    def printFoo2(self):
        print "~~~~~~~~~~~~~~~~~~~~~ Train Net Parameters ~~~~~~~~~~~~~~~~~~~~~"
        params_names = self.solver2.net.params.keys()
        print params_names
        print self.solver2.net.params[params_names[0]][0].data[0:3,:]
        print "~~~~~~~~~~~~~~~~~~~~~ Policy Net Parameters ~~~~~~~~~~~~~~~~~~~~~"
        params_names = self.policy.net.params.keys()
        print params_names
        print self.policy.net.params[params_names[0]][0].data[0:3,:]

