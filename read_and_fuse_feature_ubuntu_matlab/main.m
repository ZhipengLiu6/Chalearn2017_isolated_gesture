%
%main program for reading and fusing c3d feature
clear;
%%setting path of c3d feature
rgbtrainC3dPath = '../python/feature/train/rgb';
depthtrainC3dPath = '../python/feature/train/depth';

%%setting path
depthtrainFeaturePath = 'iso_train_only_hand_depth_map_2stream.mat';
rgbtrainFeaturePath = 'iso_train_only_hand_face_rgb_2stream.mat';


savetrainfile = 'fusion_train.mat';


ntrain = 35877; %the number of valid training sample
nvalid = 5784; %the number of valid validation sample(it also can be set 6271, the numer of testing sample)

readC3dFeature(rgbtrainC3dPath,  rgbtrainFeaturePath, ntrain);
readC3dFeature(depthtrainC3dPath, depthtrainFeaturePath, ntrain);
%%fuse training rgb and depth feature
feature_fusion(depthtrainFeaturePath, rgbtrainFeaturePath, savetrainfile, 1)
