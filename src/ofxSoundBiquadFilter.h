#pragma once

#include "ofMain.h"
#include "ofxSoundObject.h"
#include "filter_includes.h"

class ofxSoundBiquadFilter: public ofxSoundObject{
public:
    ofxSoundBiquadFilter();
//    :type(TYPE_FO_APF){
//        setAParams();
////        paramsListeners = parameters.parameterChangedE().newListener(this, &ofxBiquadFilter::paramsChanged);
//        paramsListeners.push(TypeParam.newListener(this, &ofxBiquadFilter::typeParamChanged));
//        paramsListeners.push(Freq.newListener(this, &ofxBiquadFilter::paramsChanged));
//        paramsListeners.push(Q.newListener(this, &ofxBiquadFilter::paramsChanged));
//        paramsListeners.push(Gain.newListener(this, &ofxBiquadFilter::paramsChanged));
//        paramsListeners.push(BandWidth.newListener(this, &ofxBiquadFilter::paramsChanged));
//        
//        
//    }
    
//    void updateCoeffs(int fs);
//    {
//        for(auto& filter: filters){
//            if(filter)filter->calculate_coeffs( a_freq, a_q, a_gain, a_bandWidth, fs);
//        }
//    }

//    void checkFilters(int numChannels);
//    {
//        if(bRebuildFilters){
//            filters.clear();
//            bRebuildFilters = false;
//            a_bUpdateCoeffs = true;
//        }
//        
//        while(filters.size()<numChannels) {
//            
//            FilterType t = type;
//            switch(t){
//                case TYPE_FO_APF: filters.emplace_back(std::make_unique<FO_APF>()); break;
//                case TYPE_FO_HPF: filters.emplace_back(std::make_unique<FO_HPF>()); break;
//                case TYPE_FO_LPF: filters.emplace_back(std::make_unique<FO_LPF>()); break;
//                case TYPE_FO_SHELVING_HIGH: filters.emplace_back(std::make_unique<FO_SHELVING_HIGH>()); break;
//                case TYPE_FO_SHELVING_LOW: filters.emplace_back(std::make_unique<FO_SHELVING_LOW>()); break;
//                case TYPE_SO_APF: filters.emplace_back(std::make_unique<SO_APF>()); break;
//                case TYPE_SO_BPF: filters.emplace_back(std::make_unique<SO_BPF>()); break;
//                case TYPE_SO_BSF: filters.emplace_back(std::make_unique<SO_BSF>()); break;
//                case TYPE_SO_BUTTERWORTH_BPF: filters.emplace_back(std::make_unique<SO_BUTTERWORTH_BPF>()); break;
//                case TYPE_SO_BUTTERWORTH_BSF: filters.emplace_back(std::make_unique<SO_BUTTERWORTH_BSF>()); break;
//                case TYPE_SO_BUTTERWORTH_HPF: filters.emplace_back(std::make_unique<SO_BUTTERWORTH_HPF>()); break;
//                case TYPE_SO_BUTTERWORTH_LPF: filters.emplace_back(std::make_unique<SO_BUTTERWORTH_LPF>()); break;
//                case TYPE_SO_HPF: filters.emplace_back(std::make_unique<SO_HPF>()); break;
//                case TYPE_SO_LINKWITZ_RILEY_HPF: filters.emplace_back(std::make_unique<SO_LINKWITZ_RILEY_HPF>()); break;
//                case TYPE_SO_LINKWITZ_RILEY_LPF: filters.emplace_back(std::make_unique<SO_LINKWITZ_RILEY_LPF>()); break;
//                case TYPE_SO_LPF: filters.emplace_back(std::make_unique<SO_LPF>()); break;
//                case TYPE_SO_PARAMETRIC_CQ_BOOST: filters.emplace_back(std::make_unique<SO_PARAMETRIC_CQ_BOOST>()); break;
//                case TYPE_SO_PARAMETRIC_CQ_CUT: filters.emplace_back(std::make_unique<SO_PARAMETRIC_CQ_CUT>()); break;
//                case TYPE_SO_PARAMETRIC_NCQ: filters.emplace_back(std::make_unique<SO_PARAMETRIC_NCQ>()); break;
//            }
//            
//            
//            
//        }
//    }


    void process(ofSoundBuffer &input, ofSoundBuffer &output);
//    {
//        int numChannels = output.getNumChannels();
//        checkFilters(numChannels);
//        if(a_bUpdateCoeffs){
//            updateCoeffs(output.getSampleRate());
//            a_bUpdateCoeffs = false;
//        }
//        
//        size_t index = 0;
//        auto nf = output.getNumFrames();
//        for(int i = 0; i < nf; i++) {
//            for(int c = 0; c < numChannels; c++) {
//            index = (i* numChannels) + c;
//                output[index] = filters[c]->process(input[index]);
//            }
//        }
//        
//    }
    ofParameter<float> Freq = {"Freq", 5000, 10, 20000};
    ofParameter<float> Q = {"Q", 1, 0, 10};
    ofParameter<float> Gain = {"Gain", 0, -10, 10};
    ofParameter<float> BandWidth = {"Bandwidth", 10, 0, 1000};
    ofParameter<int> TypeParam = {"Filter type", 0, 0, 18};
    ofParameterGroup parameters = {"Biquad Filter", Freq, Q, Gain, BandWidth, TypeParam};
    
    
    enum FilterType{
        TYPE_FO_APF = 0, //First order all-pass filter
        TYPE_FO_HPF, //First order high-pass filter
        TYPE_FO_LPF, //First order low-pass filter
        TYPE_FO_SHELVING_HIGH, //First order high-shelving filter
        TYPE_FO_SHELVING_LOW, //First order low-shelving filter
        TYPE_SO_APF, //Second order all-pass filter
        TYPE_SO_BPF, //Second order band-pass filter
        TYPE_SO_BSF, //Second order band-stop filter
        TYPE_SO_BUTTERWORTH_BPF, //Second order Butterworth band-pass filter
        TYPE_SO_BUTTERWORTH_BSF, //Second order Butterworth band-stop filter
        TYPE_SO_BUTTERWORTH_HPF, //Second order Butterworth high-pass filter
        TYPE_SO_BUTTERWORTH_LPF, //Second order Butterworth low-pass filter
        TYPE_SO_HPF, //Second order high-pass filter
        TYPE_SO_LINKWITZ_RILEY_HPF, //Second order Linkwitz-Riley high-pass filter
        TYPE_SO_LINKWITZ_RILEY_LPF, //Second order Linkwitz-Riley low-pass filter
        TYPE_SO_LPF, //Second order Low-pass filter
        TYPE_SO_PARAMETRIC_CQ_BOOST, //Second order parametric/peaking boost filter with constant-Q
        TYPE_SO_PARAMETRIC_CQ_CUT, //Second order parametric/peaking cut filter with constant-Q
        TYPE_SO_PARAMETRIC_NCQ, //Second order parametric/peaking filter with non-constant-Q

    };
    
    void setType(FilterType t);
//    {
//        type = t;
//        bRebuildFilters = true;
//    }

    FilterType getType();
//    {
//        return type;
//    }

protected:
    void updateCoeffs(int fs);

    void checkFilters(int numChannels);
    
    std::atomic<FilterType> type;
    void typeParamChanged(int& t);
//    {
//        setType(FilterType(t));
//    }
    vector<std::unique_ptr<Biquad>> filters;
    std::atomic<bool> bRebuildFilters = true;
    ofEventListeners paramsListeners;
    void paramsChanged(float&);
//    {
//        std::lock_guard<std::mutex> lck(paramsMutex);
//        setAParams();
//    }
    void setAParams();
//    {
//        a_freq = Freq.get();
//        a_q = Q.get();
//        a_gain = Gain.get();
//        a_bandWidth = BandWidth.get();
//        a_bUpdateCoeffs = true;
//    }
    ofMutex paramsMutex;
    float a_freq;
    float a_q ;
    float a_gain;
    float a_bandWidth;
    bool a_bUpdateCoeffs = false;
};
