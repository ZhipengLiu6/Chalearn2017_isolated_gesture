function [ ans ] = readC3dFeature( sumpath, savePath, nsample )
%UNTITLED2 Summary of this function goes here
%   read gesture feature data getting from c3d finetuned model
%sumpath = '/home/zhipengliu/ChaLearn2017/IsoGesture/feature/c3d_only_hand/validation/RGB_vgg_on_sports';
Files = dir(fullfile(sumpath));
lengthFile = length(Files); 
start = 3;
nfmax = -1;
nfmean = 0;
nv = 0;
nfsum = 0;
cnt = 0;
nsample = nsample;
feature = zeros(nsample, 4096);
label = zeros(nsample, 1);
videoid = zeros(1, nsample);
for i = start  : lengthFile%%label video
    sprintf('-------------lable = %d------------', i - 2)
    subfilename = Files(i).name;
    subfilepath = [sumpath, '/', subfilename];
    labelvideofile = dir(fullfile(subfilepath));
    sublength = length(labelvideofile);
    for j = start : sublength
        nv = nv + 1;
        videoname = labelvideofile(j).name;
        videopath = [subfilepath, '/', videoname];
        oneVideoId = str2double(videoname(1, 3 : size(videoname, 2)));
        
        featurefile = dir(fullfile(videopath));
        featureLength = length(featurefile);
        
        nfsum = nfsum + featureLength - 2;
        if nfmax < featureLength - 2
            nfmax = featureLength - 2;
        end
        for k = start : featureLength
            cnt = cnt + 1
            featurename = featurefile(k).name;
            featurepath = [videopath, '/', featurename]
            [s, data] = read_binary_blob(featurepath);%%L2 normalization
            feature(cnt, :) = data;
            label(cnt, :) = i - start;
            videoid(1, cnt) = oneVideoId;
        end
    end
end
nfmean = nfsum / nv
nfmax
save(savePath, 'feature', 'label', 'videoid', '-v7.3')
end

