#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class TestSynthAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit TestSynthAudioProcessorEditor(TestSynthAudioProcessor&);
    ~TestSynthAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    TestSynthAudioProcessor& processorRef;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TestSynthAudioProcessorEditor)
};
