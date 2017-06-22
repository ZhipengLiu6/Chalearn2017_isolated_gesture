%
%main program for reading and fusing c3d feature
clear;
%%setting path
rgbtrainC3dPath = '/home/zhipengliu/ChaLearn2017/IsoGesture/feature/c3d_only_face_hand/train/only_face_hand_rgb_2stream';
rgbvalidationC3dPath = '/home/zhipengliu/ChaLearn2017/IsoGesture/feature/c3d_only_face_hand/validation/only_face_hand_rgb_2streams';

depthtrainC3dPath = '/home/zhipengliu/ChaLearn2017/IsoGesture/feature/c3d_only_hand/training/depth_2streams';
depthvalidationC3dPath = '/home/zhipengliu/ChaLearn2017/IsoGesture/feature/c3d_only_hand/validation/depth_2streams';

depthtrainFeaturePath = '/home/zhipengliu/ChaLearn2017/IsoGesture/feature/process/only_face_hand/new_iso_train_only_hand_depth_map_2stream.mat';
rgbtrainFeaturePath = '/home/zhipengliu/ChaLearn2017/IsoGesture/feature/process/only_face_hand/new_iso_train_only_hand_face_rgb_2stream.mat';

depthvalidationFeaturePath = '/home/zhipengliu/ChaLearn2017/IsoGesture/feature/process/only_face_hand/new_iso_validation_only_hand_depth_map_2stream.mat';
rgbvalidationFeaturePath = '/home/zhipengliu/ChaLearn2017/IsoGesture/feature/process/only_face_hand/new_so_validation_only_hand_face_rgb_2stream.mat';

savetrainfile = '/home/zhipengliu/ChaLearn2017/IsoGesture/feature/process/fusion/new_iso_training_fusion_depth_map_only_hand_rgb_only_hand_face_2stream.mat';
savevalidationfile = '/home/zhipengliu/ChaLearn2017/IsoGesture/feature/process/fusion/new_iso_validation_fusion_depth_map_only_hand_rgb_only_hand_face_2stream.mat';


ntrain = 35877; %the number of valid training sample
nvalid = 5784; %the number of valid validation sample(it also can be set 6271, the numer of testing sample)

readC3dFeature(rgbtrainC3dPath,  rgbtrainFeaturePath, ntrain);
readC3dFeature(rgbvalidationC3dPath, rgbvalidationFeaturePath, nvalid);
readC3dFeature(depthtrainC3dPath, depthtrainFeaturePath, ntrain);
readC3dFeature(depthvalidationC3dPath, depthvalidationFeaturePath, nvalid);

feature_fusion(depthtrainFeaturePath, rgbtrainFeaturePath, depthvalidationFeaturePath, rgbvalidationFeaturePath, savetrainfile, savevalidationfile)

