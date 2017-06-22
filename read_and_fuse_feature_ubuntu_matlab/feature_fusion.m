function [ output_args ] = feature_fusion( trfeaturePath1, trfeaturePath2, vafeaturePath1, vafeaturePath2, savetrainfile, savevalidationfile )
%UNTITLED3 Summary of this function goes here
%   fusion the c3d fc6 feature
% trfeaturePath1 = '/home/zhipengliu/ChaLearn2017/IsoGesture/feature/process/only_face_hand/iso_train_only_hand_face_depth_2stream_rgbLabel2depth.mat';
% trfeaturePath2 = '/home/zhipengliu/ChaLearn2017/IsoGesture/feature/process/only_face_hand/iso_train_only_face_hand_rgb_2streams.mat';
% 
% vafeaturePath1 = '/home/zhipengliu/ChaLearn2017/IsoGesture/feature/process/only_face_hand/iso_validation_only_hand_face_depth_ori_2streams_rgbLabel2depth.mat';
% vafeaturePath2 = '/home/zhipengliu/ChaLearn2017/IsoGesture/feature/process/only_face_hand/iso_validation_only_face_hand_rgb_2stream_no_flap.mat';
% 
% savetrainfile = '/home/zhipengliu/ChaLearn2017/IsoGesture/feature/process/fusion/iso_training_fusion_depth_only_hand_face_rgbLabel2depth_rgb_only_hand_face_2streams.mat';
% savevalidationfile = '/home/zhipengliu/ChaLearn2017/IsoGesture/feature/process/fusion/iso_validation_fusion_depth_only_hand_face_rgbLabel2depth_rgb_only_hand_face_2streams.mat';

trfeatureDepth = load(trfeaturePath1);
trfeatureRGB = load(trfeaturePath2);

trainsize1 = size(trfeatureDepth.feature);
trainsize2 = size(trfeatureRGB.feature);
if trainsize1(1) == trainsize2(1)
    trainfeature = cat(2, trfeatureDepth.feature, trfeatureRGB.feature);
    trainlabel = trfeatureDepth.label;
    trainVideoid = trfeatureDepth.videoid;
else
    nsample = min(trainsize1(1), trainsize2(1));
    trainfeature = zeros(nsample, 4096 * 2);
    trainlabel = zeros(nsample, 1);
    trainVideoid = zeros(1, nsample);
    cntf  = 1;
    for i_1 = 1 : trainsize1(1)
        for i = 1 :  trainsize2(1)
            if trfeatureDepth.videoid(1, i_1) == trfeatureRGB.videoid(1, i)
                trainfeature(cntf, 1 : 4096) = trfeatureDepth.feature(i_1, 1 : 4096);
                trainfeature(cntf, 4097 : 4096 * 2) = trfeatureRGB.feature(i, 1 : 4096);
                trainlabel(cntf, 1) = trfeatureDepth.label(i_1, 1);
                trainVideoid(cntf , 1) = trfeatureDepth.videoid(1, i_1);
                cntf = cntf + 1
                break;                
            end           
        end
    end
end

save(savetrainfile, 'trainfeature', 'trainlabel', 'trainVideoid', '-v7.3');


vafeatureDepth = load(vafeaturePath1);
vafeatureRGB = load(vafeaturePath2);
validationSize1 = size(vafeatureDepth.feature);
validationSize2 = size(vafeatureRGB.feature);
if validationSize1(1) == validationSize2(1)
    validationfeature = cat(2, vafeatureDepth.feature, vafeatureRGB.feature);
    validationlabel = vafeatureDepth.label;
    validationVideoid = vafeatureDepth.videoid;
else
    nsample = min(validationSize1(1), validationSize2(1));
    validationfeature = zeros(nsample, 4096 * 2);
    validationlabel = zeros(nsample, 1);
    validationVideoid = zeros(1, nsample);
    cntf  = 1;
    for i_1 = 1 : validationSize1(1)
        for i = 1 :  validationSize2(1)
            if vafeatureDepth.videoid(1, i_1) == vafeatureRGB.videoid(1, i)
                validationfeature(cntf, 1 : 4096) = vafeatureDepth.feature(i_1, 1 : 4096);
                validationfeature(cntf, 4097 : 4096 * 2) = vafeatureRGB.feature(i, 1 : 4096);
                validationlabel(cntf, 1) = vafeatureDepth.label(i_1, 1);
                validationVideoid(cntf, 1) = vafeatureDepth.videoid(1, i_1);
                cntf = cntf + 1
                break;                
            end           
        end
    end
end
save(savevalidationfile, 'validationfeature', 'validationlabel', 'validationVideoid', '-v7.3');
end

