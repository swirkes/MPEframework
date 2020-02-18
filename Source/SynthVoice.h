/*
  ==============================================================================

    SynthVoice.h
    Created: 4 Feb 2020 12:24:44pm
    Author:  shane wirkes

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "maximilian.h"



class SynthVoice : public SynthesiserVoice
{
public:
    bool canPlaySound (SynthesiserSound* sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }
    
    //===========================================================================
    
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        env1.trigger = 1;
        level = velocity;
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        std::cout << midiNoteNumber << std::endl;
        
    }
    //===========================================================================
    void stopNote (float velocity, bool allowTailOff)
    {
        env1.trigger = 0;
        allowTailOff = true;
        
        if(velocity == 0)
            clearCurrentNote();
       
    }
    
    //===========================================================================
    void isVoiceActive()
    {
        
    }
    //===========================================================================
    void pitchWheelMoved (int newPitchWheelValue)
    {
        
    }
    //===========================================================================
    void controllerMoved (int controllerNumber, int newControllerValue)
    {
        
    }
    
    //===========================================================================
    void aftertouchChanged (int newChannelPressureValue)
    {
        
    }
    
    //===========================================================================
    void channelPressureChanged (int newChannelPressureValue)
    {
        
    }
    
    //===========================================================================
    void renderNextBlock (AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
    {
        env1.setAttack(2000);
        env1.setDecay(500);
        env1.setSustain(0.8);
        env1.setRelease(2000);
        
        for (int sample = 0; sample < numSamples; ++sample)
        {
            double theWave = osc1.sinewave(frequency) /* * frequency*/;
            double theSound = env1.adsr(theWave, env1.trigger) * level;
            double filteredSound = filter1.lores(theSound, 100, 0.1);
            
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, filteredSound);
            }
            ++startSample;
        }
    }
    //===========================================================================
    void setCurrentPlaybackSampleRate (double newRate)
    {
        
    }
    //===========================================================================

    bool isPlayingChannel(int midiChannel)
    {
        return true;
    }
    
private:
    double frequency;
    double level;
    
    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter filter1;
    
};
