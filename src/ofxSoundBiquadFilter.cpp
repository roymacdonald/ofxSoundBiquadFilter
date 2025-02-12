#include "ofxSoundBiquadFilter.h"


ofxSoundBiquadFilter::ofxSoundBiquadFilter():type(TYPE_FO_APF){
    setAParams();
    paramsListeners.push(TypeParam.newListener(this, &ofxSoundBiquadFilter::typeParamChanged));
    paramsListeners.push(Freq.newListener(this, &ofxSoundBiquadFilter::paramsChanged));
    paramsListeners.push(Q.newListener(this, &ofxSoundBiquadFilter::paramsChanged));
    paramsListeners.push(Gain.newListener(this, &ofxSoundBiquadFilter::paramsChanged));
    paramsListeners.push(BandWidth.newListener(this, &ofxSoundBiquadFilter::paramsChanged));
    
    
}
//-----------------------------------------------------------------------------------------
void ofxSoundBiquadFilter::updateCoeffs(int fs){
    for(auto& filter: filters){
        if(filter)filter->calculate_coeffs( a_freq, a_q, a_gain, a_bandWidth, fs);
    }
}

//-----------------------------------------------------------------------------------------
void ofxSoundBiquadFilter::checkFilters(int numChannels){
    if(bRebuildFilters){
        filters.clear();
        bRebuildFilters = false;
        a_bUpdateCoeffs = true;
    }
    
    while(filters.size()<numChannels) {
        
        FilterType t = type;
        switch(t){
            case TYPE_FO_APF: filters.emplace_back(std::make_unique<FO_APF>()); break;
            case TYPE_FO_HPF: filters.emplace_back(std::make_unique<FO_HPF>()); break;
            case TYPE_FO_LPF: filters.emplace_back(std::make_unique<FO_LPF>()); break;
            case TYPE_FO_SHELVING_HIGH: filters.emplace_back(std::make_unique<FO_SHELVING_HIGH>()); break;
            case TYPE_FO_SHELVING_LOW: filters.emplace_back(std::make_unique<FO_SHELVING_LOW>()); break;
            case TYPE_SO_APF: filters.emplace_back(std::make_unique<SO_APF>()); break;
            case TYPE_SO_BPF: filters.emplace_back(std::make_unique<SO_BPF>()); break;
            case TYPE_SO_BSF: filters.emplace_back(std::make_unique<SO_BSF>()); break;
            case TYPE_SO_BUTTERWORTH_BPF: filters.emplace_back(std::make_unique<SO_BUTTERWORTH_BPF>()); break;
            case TYPE_SO_BUTTERWORTH_BSF: filters.emplace_back(std::make_unique<SO_BUTTERWORTH_BSF>()); break;
            case TYPE_SO_BUTTERWORTH_HPF: filters.emplace_back(std::make_unique<SO_BUTTERWORTH_HPF>()); break;
            case TYPE_SO_BUTTERWORTH_LPF: filters.emplace_back(std::make_unique<SO_BUTTERWORTH_LPF>()); break;
            case TYPE_SO_HPF: filters.emplace_back(std::make_unique<SO_HPF>()); break;
            case TYPE_SO_LINKWITZ_RILEY_HPF: filters.emplace_back(std::make_unique<SO_LINKWITZ_RILEY_HPF>()); break;
            case TYPE_SO_LINKWITZ_RILEY_LPF: filters.emplace_back(std::make_unique<SO_LINKWITZ_RILEY_LPF>()); break;
            case TYPE_SO_LPF: filters.emplace_back(std::make_unique<SO_LPF>()); break;
            case TYPE_SO_PARAMETRIC_CQ_BOOST: filters.emplace_back(std::make_unique<SO_PARAMETRIC_CQ_BOOST>()); break;
            case TYPE_SO_PARAMETRIC_CQ_CUT: filters.emplace_back(std::make_unique<SO_PARAMETRIC_CQ_CUT>()); break;
            case TYPE_SO_PARAMETRIC_NCQ: filters.emplace_back(std::make_unique<SO_PARAMETRIC_NCQ>()); break;
        }
        
        
        
    }
}

//-----------------------------------------------------------------------------------------

void ofxSoundBiquadFilter::process(ofSoundBuffer &input, ofSoundBuffer &output) {
    int numChannels = output.getNumChannels();
    checkFilters(numChannels);
    if(a_bUpdateCoeffs){
        updateCoeffs(output.getSampleRate());
        a_bUpdateCoeffs = false;
    }
    
    size_t index = 0;
    auto nf = output.getNumFrames();
    for(int i = 0; i < nf; i++) {
        for(int c = 0; c < numChannels; c++) {
            index = (i* numChannels) + c;
            output[index] = filters[c]->process(input[index]);
        }
    }
    
}

//-----------------------------------------------------------------------------------------
void ofxSoundBiquadFilter::setType(ofxSoundBiquadFilter::FilterType t){
    type = t;
    bRebuildFilters = true;
}
//-----------------------------------------------------------------------------------------
ofxSoundBiquadFilter::FilterType ofxSoundBiquadFilter::getType(){
    return type;
}

//-----------------------------------------------------------------------------------------
void ofxSoundBiquadFilter::typeParamChanged(int& t){
    setType(FilterType(t));
}
//-----------------------------------------------------------------------------------------

void ofxSoundBiquadFilter::paramsChanged(float&){
    std::lock_guard<std::mutex> lck(paramsMutex);
    setAParams();
}
//-----------------------------------------------------------------------------------------
void ofxSoundBiquadFilter::setAParams(){
    a_freq = Freq.get();
    a_q = Q.get();
    a_gain = Gain.get();
    a_bandWidth = BandWidth.get();
    a_bUpdateCoeffs = true;
}
