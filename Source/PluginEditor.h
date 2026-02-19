#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
class PartialsLookAndFeel : public juce::LookAndFeel_V4
{
public:
    PartialsLookAndFeel()
    {
        setColour(juce::Slider::rotarySliderFillColourId,    juce::Colour(0xffe8a84b));
        setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour(0xff2e2e2e));
        setColour(juce::Slider::thumbColourId,               juce::Colour(0xffe8a84b));
        setColour(juce::Label::textColourId,                 juce::Colour(0xffa0a0a0));
    }

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                          float sliderPosProportional, float rotaryStartAngle,
                          float rotaryEndAngle, juce::Slider& slider) override
    {
        juce::ignoreUnused(slider);

        const float radius  = (float) juce::jmin(width / 2, height / 2) - 6.0f;
        const float centreX = (float) x + (float) width  * 0.5f;
        const float centreY = (float) y + (float) height * 0.5f;
        const float angle   = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

        // Track arc (background)
        {
            juce::Path track;
            track.addCentredArc(centreX, centreY, radius, radius, 0.0f,
                                rotaryStartAngle, rotaryEndAngle, true);
            g.setColour(juce::Colour(0xff2e2e2e));
            g.strokePath(track, juce::PathStrokeType(4.0f, juce::PathStrokeType::curved,
                                                     juce::PathStrokeType::rounded));
        }

        // Value arc (filled)
        {
            juce::Path valueArc;
            valueArc.addCentredArc(centreX, centreY, radius, radius, 0.0f,
                                   rotaryStartAngle, angle, true);
            g.setColour(juce::Colour(0xffe8a84b));
            g.strokePath(valueArc, juce::PathStrokeType(4.0f, juce::PathStrokeType::curved,
                                                        juce::PathStrokeType::rounded));
        }

        // Thumb dot
        const float thumbRadius = 4.0f;
        const float thumbX = centreX + (radius - 4.0f) * std::cos(angle - juce::MathConstants<float>::halfPi);
        const float thumbY = centreY + (radius - 4.0f) * std::sin(angle - juce::MathConstants<float>::halfPi);
        g.setColour(juce::Colour(0xffe8a84b));
        g.fillEllipse(thumbX - thumbRadius, thumbY - thumbRadius,
                      thumbRadius * 2.0f, thumbRadius * 2.0f);

        // Inner circle
        const float innerRadius = radius * 0.55f;
        g.setColour(juce::Colour(0xff242424));
        g.fillEllipse(centreX - innerRadius, centreY - innerRadius,
                      innerRadius * 2.0f, innerRadius * 2.0f);

        // Inner circle border
        g.setColour(juce::Colour(0xff3a3a3a));
        g.drawEllipse(centreX - innerRadius, centreY - innerRadius,
                      innerRadius * 2.0f, innerRadius * 2.0f, 1.0f);
    }
};

//==============================================================================
class TestSynthAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit TestSynthAudioProcessorEditor(TestSynthAudioProcessor&);
    ~TestSynthAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    TestSynthAudioProcessor& processorRef;

    PartialsLookAndFeel lnf;

    juce::Slider gainSlider;
    juce::Label  gainLabel;
    juce::AudioProcessorValueTreeState::SliderAttachment gainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TestSynthAudioProcessorEditor)
};
