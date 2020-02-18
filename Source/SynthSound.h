/*
  ==============================================================================

    SynthSound.h
    Created: 4 Feb 2020 12:24:35pm
    Author:  shane wirkes

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SynthSound : public SynthesiserSound
{
public:
    bool appliesToNote(int /*midiNoteNumber*/)
    {
        return true;
    }
                        
    bool appliesToChannel(int /*midiChannel*/)
    {
        return true;
    }
                            
                            
    
};
