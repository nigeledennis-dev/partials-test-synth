#include "PluginEditor.h"

TestSynthAudioProcessorEditor::TestSynthAudioProcessorEditor(TestSynthAudioProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p)
{
    setSize(800, 500);
}

TestSynthAudioProcessorEditor::~TestSynthAudioProcessorEditor() {}

void TestSynthAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xff1a1a1a));
    g.setColour(juce::Colours::white);
    g.setFont(16.0f);
    g.drawFittedText("Test Synth", getLocalBounds(), juce::Justification::centred, 1);
}

void TestSynthAudioProcessorEditor::resized()
{
}
