#include "PluginEditor.h"

//==============================================================================
// Colour palette
static const juce::Colour colBackground   { 0xff1a1a1a };
static const juce::Colour colSurface      { 0xff242424 };
static const juce::Colour colPanelBorder  { 0xff333333 };
static const juce::Colour colHeaderBg     { 0xff111111 };
static const juce::Colour colAccent       { 0xffe8a84b };
static const juce::Colour colTextPrimary  { 0xffffffff };
static const juce::Colour colTextSecondary{ 0xff888888 };
static const juce::Colour colDivider      { 0xff2a2a2a };

//==============================================================================
TestSynthAudioProcessorEditor::TestSynthAudioProcessorEditor(TestSynthAudioProcessor& p)
    : AudioProcessorEditor(&p),
      processorRef(p),
      gainAttachment(p.apvts, "gain", gainSlider)
{
    setLookAndFeel(&lnf);

    // Gain slider – rotary style
    gainSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    gainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    gainSlider.setPopupDisplayEnabled(true, false, this);
    addAndMakeVisible(gainSlider);

    // Gain label
    gainLabel.setText("GAIN", juce::dontSendNotification);
    gainLabel.setFont(juce::Font(11.0f, juce::Font::plain).withExtraKerningFactor(0.15f));
    gainLabel.setJustificationType(juce::Justification::centred);
    gainLabel.setColour(juce::Label::textColourId, colTextSecondary);
    addAndMakeVisible(gainLabel);

    setSize(800, 500);
}

TestSynthAudioProcessorEditor::~TestSynthAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void TestSynthAudioProcessorEditor::paint(juce::Graphics& g)
{
    auto      bounds  = getLocalBounds();
    const int headerH = 56;
    const int footerH = 28;

    // ── Background ──────────────────────────────────────────────────────────
    g.fillAll(colBackground);

    // ── Header ──────────────────────────────────────────────────────────────
    const auto headerArea = bounds.removeFromTop(headerH).toFloat();
    g.setColour(colHeaderBg);
    g.fillRect(headerArea);

    // Bottom border of header
    g.setColour(colDivider);
    g.fillRect(headerArea.getX(), headerArea.getBottom() - 1.0f,
               headerArea.getWidth(), 1.0f);

    // Accent left bar
    g.setColour(colAccent);
    g.fillRect(0.0f, headerArea.getY(), 3.0f, headerArea.getHeight());

    // Plugin name
    g.setColour(colTextPrimary);
    g.setFont(juce::Font(18.0f, juce::Font::bold));
    g.drawText("TEST SYNTH",
               juce::Rectangle<float>(20.0f, headerArea.getY(),
                                      300.0f, (float) headerH),
               juce::Justification::centredLeft, false);

    // Brand tag
    g.setColour(colTextSecondary);
    g.setFont(juce::Font(10.0f, juce::Font::plain).withExtraKerningFactor(0.2f));
    g.drawText("PARTIALS",
               juce::Rectangle<float>((float) bounds.getWidth() - 90.0f,
                                      headerArea.getY(),
                                      80.0f, (float) headerH),
               juce::Justification::centredRight, false);

    // ── Control panel card ───────────────────────────────────────────────────
    const float cardW = 140.0f;
    const float cardH = 200.0f;
    const float cardX = ((float) getWidth() - cardW) * 0.5f;
    const float cardY = (float) headerH + ((float) (getHeight() - headerH - footerH) - cardH) * 0.5f;

    const juce::Rectangle<float> card(cardX, cardY, cardW, cardH);

    // Card shadow (simple layered rects)
    g.setColour(juce::Colour(0x18000000));
    g.fillRoundedRectangle(card.expanded(4.0f), 10.0f);
    g.setColour(juce::Colour(0x10000000));
    g.fillRoundedRectangle(card.expanded(8.0f), 12.0f);

    // Card fill
    g.setColour(colSurface);
    g.fillRoundedRectangle(card, 8.0f);

    // Card border
    g.setColour(colPanelBorder);
    g.drawRoundedRectangle(card, 8.0f, 1.0f);

    // ── Footer ───────────────────────────────────────────────────────────────
    const juce::Rectangle<float> footer((float) bounds.getX(),
                                        (float) getHeight() - footerH,
                                        (float) getWidth(), (float) footerH);
    g.setColour(colHeaderBg);
    g.fillRect(footer);

    g.setColour(colDivider);
    g.fillRect(footer.getX(), footer.getY(), footer.getWidth(), 1.0f);

    g.setColour(colTextSecondary);
    g.setFont(juce::Font(9.0f, juce::Font::plain).withExtraKerningFactor(0.1f));
    g.drawText("v1.0.0", footer, juce::Justification::centredRight, false);
}

//==============================================================================
void TestSynthAudioProcessorEditor::resized()
{
    const int headerH  = 56;
    const int footerH  = 28;
    const int knobSize = 100;
    const int labelH   = 24;

    // Knob centred in the window (excluding header/footer)
    const int workH = getHeight() - headerH - footerH;
    const int knobX = (getWidth()  - knobSize) / 2;
    const int knobY = headerH + (workH - knobSize - labelH - 4) / 2;

    gainSlider.setBounds(knobX, knobY, knobSize, knobSize);
    gainLabel .setBounds(knobX - 10, knobY + knobSize + 4, knobSize + 20, labelH);
}
