#!/usr/bin/env python
# -*- coding: utf8 -*-
import scipy.io as scio
import os, sys
import pdb
import numpy as np
import time
# from svmutil import *
# from svm import *
from sklearn import svm, datasets
from sklearn.externals import joblib
import matplotlib.pyplot as plt
import h5py
import pickle
import pprint
import argparse
import subprocess
import re
"""
function: test the svm model, generate and save the accuracy
@x: feature, numpy, shape: (nsamples, nfeature)
@y: label, numpy, shape: (nsample): groundtruth
@modelPath: the saved linear model path
@saveResultPath: the pickle path, which is used to save the accuracy, prediction and  groundtruth result
@para: the trained parameter
"""
def test_has_gr(x = None, y = None, modelPath = None, saveResultPath = None, para = None):
    yg = y.squeeze()
    lin_svc = joblib.load(modelPath)
    predict = lin_svc.predict(x)
    cnt_correct = 0
    cnt_all = yg.shape[0]
    for i in range(cnt_all):
        if yg[i] == predict[i]:
            # print("i = %d, ground = %d, predict = %d" % (i, yg[i], predict[i]))
            cnt_correct = cnt_correct + 1

    acc = float(cnt_correct) / cnt_all
    
    print('accuracy: ', acc)
    # pdb.set_trace()
    result = {1 : acc,
                    2 : predict,
                    3 : yg,
                    4 : para,
    }
    # pdb.set_trace()
    saveStream = open(saveResultPath, 'wb')
    pickle.dump(result, saveStream)
    saveStream.close()
    return predict
"""
function: test the svm model, generate prediction result
@x: feature, numpy, shape: (nsamples, nfeature)
@modelPath: the saved linear model path
@saveResultPath: the pickle path, which is used to save the prediction.
@para: the trained parameter
"""
def test_no_gr(x = None, modelPath = None, saveResultPath = None, para = None):
    lin_svc = joblib.load(modelPath)
    predict = lin_svc.predict(x)
    result = {2 : predict,
                    4 : para,
    }
    # pdb.set_trace()
    saveStream = open(saveResultPath, 'wb')
    pickle.dump(result, saveStream)
    saveStream.close()
    return predict
"""
function: train and save the linear svm model
@x: feature, numpy, shape: (nsamples, nfeature)
@y: label, numpy, shape: (nsample)
@para: svm hyper-parameter
@return: none
"""
def train(x = None, y = None, saveModelPath = 'iso_training_plinear_svm_model_max_iter_2w.m', para = None):
    # pdb.set_trace()
    y = y.squeeze()
    ## set hyper-parameter
    print("begin training")
    C = para['C']
    dual = para['dual']
    class_weight = para['class_weight']
    max_iter = para['max_iter']

    lin_svc = svm.LinearSVC(C = C, dual = dual, class_weight = class_weight).fit(x, y)
    # pdb.set_trace()
    joblib.dump(lin_svc, saveModelPath)
    print("training done!")
"""
function: generate submission prediction file as the format of https://competitions.codalab.org/competitions/16491#learn_the_details-evaluation
@videoid: the id of predicted video: (1, nsample)
@predict: prediction result
@mysubfile: the file of submission
@GivenVideolistfile: the official given test video list file
@isTest: 1 : generate validation submission file; 2 : generate testing submission file 
"""
def Generate_submission_file(videoid = None,  predict = None, mysubfile = None, GivenVideolistfile = None, isTest = 1):
    videoid = videoid.squeeze()
    r = re.compile('[ \t\n\r:,/]+')
    result_class = predict
    NumAviVideo = videoid.shape[0]
    resultvideoDic = {-1: -1}           #videoid to result lineid
    for i in range(NumAviVideo):
        onevideoId = videoid[i]
        resultvideoDic[onevideoId] = i

    test_stream = open(GivenVideolistfile, 'r')
    testAllline = test_stream.readlines()
    test_stream.close()

    substream = open(mysubfile, 'w')
    numlen = len(testAllline)
    for i in range(numlen):
        oritestline = testAllline[i]
        if isTest == 2:
            onevideoId = int(oritestline[11: 16])
        elif isTest == 1:
            onevideoId = int(oritestline[12: 17])
        else:
            print("The parameter isTest is wrong!!")
            sys.exit()
        linelen = len(oritestline)
        if resultvideoDic.has_key(onevideoId):
            lineid = resultvideoDic[onevideoId]
            lable = int(result_class[lineid]) + 1
        else:
            lable = 1
        newtestline = oritestline[0 : linelen-1] + " " + str(lable) + "\n"
        substream.write(newtestline)
    substream.close()

def checkPath(path = None):
    if not os.path.exists(path):
        strcmd = "mkdir -p " + path
        subprocess.call(strcmd, shell = True)   
if __name__ == '__main__':
    ##set data path
    parser = argparse.ArgumentParser()
    parser.add_argument('--trainfilepath', default='../read_and_fuse_feature_ubuntu_matlab/fusion_train.mat', type=str, help = 'the path to fusion c3d training feature file')
    parser.add_argument('--testfilepath', default='../read_and_fuse_feature_ubuntu_matlab//fusion_test.mat', type=str, help = 'the path to fusion c3d testing feature file')
    parser.add_argument('--submissionFile', default='submission/valid_prediction.txt', type=str, help = 'the path to submission file')
    parser.add_argument('--GivenVideolistfile', default='data/valid_list.txt', type=str, help = 'the path to given submission video list file')
    parser.add_argument('--submissionType', default=1, type=int, help = 'the submission data type(1: valid, 2: test) ')
    parser.add_argument('--isTrain', default=1, type=int, help = 'whether to run the training svm code(1: run, 0: do not run)')
    parser.add_argument('--isTest', default=1, type=int, help = 'whether to run the testing svm code and generate submission file(1: run, 0: do not run)')
    parser.add_argument('--saveModelPath', default = "../svm_model/iso_training_linear_svm_model_depth_map_only_hand_rgb_only_hand_face_2streams_iter_1k_c_Efu1.m", type = str, help = 'the path to saved svm model')
    args = parser.parse_args()
    # pdb.set_trace()
    trainfilepath = args.trainfilepath
    testfilepath = args.testfilepath
    submissionFile = args.submissionFile
    GivenVideolistfile = args.GivenVideolistfile

    isTrain = args.isTrain
    isTest = args.isTest
    submissionType = args.submissionType
    strpara = "iso_depth_map_only_hand_rgb_only_hand_face_2streams_iter_1k_c_Efu1"
    print("experiment type:", strpara)
    saveModelPath = args.saveModelPath

    saveResultPath = 'svm_result'
    checkPath(saveResultPath)
    saveResultPath = saveResultPath + "/" + strpara + '.pkl'

    ## set hyper-parameter for svm
    para = {}
    para['C'] = 0.1
    para['dual'] = False #dual=False when n_samples > n_features.
    para['class_weight'] = 'balanced'
    para['max_iter'] = 1000
    ##-------------------------------    
    pprint.pprint(para)
    ##load data
    #------------------------------load data---------------------------------
    # trainmat = scio.loadmat(trainfilepath) #for v7.0 mat
    trainmat = h5py.File(trainfilepath)
    train_x = trainmat['trainfeature'][:]
    train_y = trainmat['trainlabel'][:]
    videoid = trainmat['trainVideoid'][:]
    train_x = train_x.transpose(1, 0)
    print("training x shape:", train_x.shape)
    print("training y shape:", train_y.shape)
    # pdb.set_trace()
    timestart = time.time()
    if isTrain == 1:
        # pdb.set_trace()
        train(x = train_x, y = train_y, saveModelPath = saveModelPath, para = para)
    #-----------------------------------------------------------------------------
    if isTest == 1:
        validationmat = h5py.File(testfilepath)
        # validationmat = scio.loadmat(testfilepath)
        validation_x = validationmat['validationfeature'][:]
        validation_y = validationmat['validationlabel'][:]
        validvideoid = validationmat['validationVideoid'][:]
        validation_x = validation_x.transpose(1, 0)
        print("testing x shape:", validation_x.shape)
        print("testing y shape:", validation_y.shape)
        print("testing the training data:")
        test_has_gr(x = train_x, y = train_y, modelPath = saveModelPath, saveResultPath = saveResultPath, para = para)
        print("testing the testing data:")
        # test_has_gr(x = validation_x, y = validation_y, modelPath = saveModelPath, saveResultPath = saveResultPath, para = para)
        predict = test_no_gr(x = validation_x, modelPath = saveModelPath, saveResultPath = saveResultPath, para = para)
        Generate_submission_file(videoid = validvideoid, predict  = predict, mysubfile = submissionFile, GivenVideolistfile = GivenVideolistfile, isTest = submissionType)
    timeend = time.time()
    print("using time: ", timeend - timestart)