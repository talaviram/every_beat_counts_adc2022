cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(APPLE)
    if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        execute_process(COMMAND xcrun --sdk macosx --show-sdk-path OUTPUT_VARIABLE CMAKE_OSX_SYSROOT)
    endif()

    set(CMAKE_XCODE_ATTRIBUTE_ARCHS "$(ARCHS_STANDARD)")
    set(CMAKE_XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH $<IF:$<CONFIG:Debug>,YES,NO>)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13" CACHE STRING "Minimum OS X deployment version")
endif()

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

project(SampleMetronome VERSION 1.0.0)

set(JUCE_ENABLE_MODULE_SOURCE_GROUPS ON CACHE BOOL INTERNAL)
set_property(GLOBAL PROPERTY USE_FOLDERS YES)

include(cmake/CPM.cmake)

CPMAddPackage(
    GITHUB_REPOSITORY "soundradix/JUCE"
    GIT_TAG "a0118d81d176d64e3c69cb16d7d82085c062984d"
    OPTIONS "JUCE_ENABLE_MODULE_SOURCE_GROUPS ON"
)

juce_add_plugin(SampleMetronome
    COMPANY_NAME "yourcompany"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    MICROPHONE_PERMISSION_ENABLED TRUE
    MICROPHONE_PERMISSION_TEXT "We use audio input in standalone JUCE app"
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE Manu
    PLUGIN_CODE Metr
    FORMATS AU VST3 Standalone
    PRODUCT_NAME "SampleMetronome"
)

juce_generate_juce_header(SampleMetronome)

target_include_directories(SampleMetronome
    PRIVATE
    Source
)

target_sources(SampleMetronome
    PRIVATE
    Source/PluginEditor.h
    Source/PluginEditor.cpp
    Source/PluginProcessor.h
    Source/PluginProcessor.cpp
    Source/TempoUtils.h
    Source/TempoUtils.cpp
)
target_compile_definitions(SampleMetronome
    PUBLIC
    DONT_SET_USING_JUCE_NAMESPACE=1

    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_DISPLAY_SPLASH_SCREEN=0
)

# juce_add_binary_data(AudioPluginData SOURCES ...)
target_link_libraries(SampleMetronome
    PRIVATE

    # AudioPluginData           # If we'd created a binary data target, we'd link to it here
    juce::juce_audio_utils
    PUBLIC
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags)
