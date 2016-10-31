clc,clear;
close all;
%% min
minA_old = [
  0, -9,-10,  0, -9,-10,-10, -9,-10,  0, -9,-10;
 -9,  0, -7, -9,  0,-10,-10, -1, -6,-10,  0,-14;
-10, -7,  0,-10,-14,  0, -9, -6, -2,-10,-13,  0;
  0, -9,-10,  0, -9,-10,  0, -9,-10,-10, -9,-10;
 -9,  0,-14, -9,  0, -6,-10,  0,-13,-10, -2, -7;
-10,-10,  0,-10, -6,  0, -9,-14,  0,-10, -7, -1;
-10,-10, -9,  0,-10, -9,  0,-10, -9,  0,-10, -9;
 -9, -1, -6, -9,  0,-14,-10,  0, -7,-10,  0,-10;
-10, -6, -2,-10,-13,  0, -9, -7,  0,-10,-15,  0;
  0,-10,-10,-10,-10,-10,  0,-10,-10,  0,-10,-10;
 -9,  0,-13, -9, -2, -7,-10,  0,-15,-10,  0, -6;
-10,-14,  0,-10, -7, -1, -9,-10,  0,-10, -6,  0];
minA_new = [
     0,   -9,  -10,  -10,   -9,  -10,  -10,   -9,  -10,  -10,   -9,  -10;
    -9,    0,   -7,  -10,   -1,   -6,  -10,   -1,   -6,  -10,   -1,   -6;
   -10,   -7,    0,   -9,   -6,   -2,   -9,   -6,   -2,   -9,   -6,   -2;
   -10,  -10,   -9,    0,   -9,  -10,  -10,   -9,  -10,  -10,   -9,  -10;
    -9,   -1,   -6,   -9,    0,   -7,  -10,   -1,   -6,  -10,   -1,   -6;
   -10,   -6,   -2,  -10,   -7,    0,   -9,   -6,   -2,   -9,   -6,   -2;
   -10,  -10,   -9,  -10,  -10,   -9,    0,   -9,  -10,  -10,   -9,  -10;
    -9,   -1,   -6,   -9,   -1,   -6,   -9,    0,   -7,  -10,   -1,   -6;
   -10,   -6,   -2,  -10,   -6,   -2,  -10,   -7,    0,   -9,   -6,   -2;
   -10,  -10,   -9,  -10,  -10,   -9,  -10,  -10,   -9,    0,   -9,  -10;
    -9,   -1,   -6,   -9,   -1,   -6,   -9,   -1,   -6,   -9,    0,   -7;
   -10,   -6,   -2,  -10,   -6,   -2,  -10,   -6,   -2,  -10,   -7,    0];

slice_old = {};
slice_new = {};
index = {};
for i = 1:4
    for j = i:4
        slice_old = [slice_old, {minA_old(3*(i-1)+1:3*i,3*(j-1)+1:3*j)}];
        slice_new = [slice_new, {minA_new(3*(i-1)+1:3*i,3*(j-1)+1:3*j)}];
        index = [index, {[i,j]}];
    end
end

fprintf('Old min A Analysis\n');
for i = 1:length(slice_old)
    fprintf('Submatrix %d, %d\n',index{i});
    disp(slice_old{i})
    [V,D] = eig(slice_old{i});
%     fprintf('Eigen Vector\n')
%     disp(V)
    fprintf('Eigen Value\n')
    disp(D)
end

fprintf('New min A Analysis\n');
for i = 1:length(slice_new)
    fprintf('Submatrix %d, %d\n',index{i});
    disp(slice_new{i})
    [V,D] = eig(slice_new{i});
%     fprintf('Eigen Vector\n')
%     disp(V)
    fprintf('Eigen Value\n')
    disp(D)
end

%% max
maxA_old = [
21,11,10, 6,11,10, 1,11,10, 6,11,10;
11,27, 7,11,20,15,10,13, 8,10,20,11;
10, 7,28,11,14,20,11, 8,12,11,15,20;
 6,11,11,21,11,11, 6,11,11, 1,11,11;
11,20,14,11,28, 8,10,20,15,10,12, 7;
10,15,20,11, 8,27,11,11,20,11, 7,13;
 1,10,11, 6,10,11,21,10,11, 6,10,11;
11,13, 8,11,20,11,10,27, 7,10,20,15;
10, 8,12,11,15,20,11, 7,28,11,14,20;
 6,10,11, 1,10,11, 6,10,11,21,10,11;
11,20,15,11,12, 7,10,20,14,10,28, 8;
10,11,20,11, 7,13,11,15,20,11, 8,27];

maxA_new = [
    21,   11,   10,    1,   11,   10,    1,   11,   10,    1,   11,   10;
    11,   27,    7,   10,   13,    8,   10,   13,    8,   10,   13,    8;
    10,    7,   28,   11,    8,   12,   11,    8,   12,   11,    8,   12;
     6,   11,   11,   21,   11,   10,    1,   11,   10,    1,   11,   10;
    11,   20,   14,   11,   27,    7,   10,   13,    8,   10,   13,    8;
    10,   15,   20,   10,    7,   28,   11,    8,   12,   11,    8,   12;
     1,   10,   11,    6,   10,   11,   21,   11,   10,    1,   11,   10;
    11,   13,    8,   11,   20,   11,   11,   27,    7,   10,   13,    8;
    10,    8,   12,   11,   15,   20,   10,    7,   28,   11,    8,   12;
     6,   10,   11,    1,   10,   11,    6,   10,   11,   21,   11,   10;
    11,   20,   15,   11,   12,    7,   10,   20,   14,   11,   27,    7;
    10,   11,   20,   11,    7,   13,   11,   15,   20,   10,    7,   28];

slice_old = {};
slice_new = {};
index = {};
for i = 1:4
    for j = i:4
        slice_old = [slice_old, {maxA_old(3*(i-1)+1:3*i,3*(j-1)+1:3*j)}];
        slice_new = [slice_new, {maxA_new(3*(i-1)+1:3*i,3*(j-1)+1:3*j)}];
        index = [index, {[i,j]}];
    end
end

% fprintf('Old max A Analysis\n');
% for i = 1:length(slice_old)
%     fprintf('Submatrix %d, %d\n',index{i});
%     disp(slice_old{i})
%     [V,D] = eig(slice_old{i});
% %     fprintf('Eigen Vector\n')
% %     disp(V)
%     fprintf('Eigen Value\n')
%     disp(D)
% end

fprintf('New max A Analysis\n');
for i = 1:length(slice_new)
    fprintf('Submatrix %d, %d\n',index{i});
    disp(slice_new{i})
    [V,D] = eig(slice_new{i});
%     fprintf('Eigen Vector\n')
%     disp(V)
    fprintf('Eigen Value\n')
    disp(D)
end
