#pragma once

#include "ofMain.h"
#include "ofxSoundObject.h"
#include "filter_includes.h"

class ofxSoundBiquadFilter: public ofxSoundObject{
public:
    ofxSoundBiquadFilter();

    void process(ofSoundBuffer &input, ofSoundBuffer &output) override;

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

    FilterType getType();

protected:
    void updateCoeffs(int fs);

    void checkFilters(int numChannels);
    
    std::atomic<FilterType> type;
    void typeParamChanged(int& t);
    vector<std::unique_ptr<Biquad>> filters;
    std::atomic<bool> bRebuildFilters = true;
    ofEventListeners paramsListeners;
    void paramsChanged(float&);
    void setAParams();
    ofMutex paramsMutex;
    float a_freq;
    float a_q ;
    float a_gain;
    float a_bandWidth;
    bool a_bUpdateCoeffs = false;
};
