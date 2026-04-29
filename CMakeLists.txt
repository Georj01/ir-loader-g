cmake_minimum_required(VERSION 3.20)
project(ir-loader-g VERSION 1.0.0)

find_package(JUCE CONFIG PATHS "C:/JUCE" NO_DEFAULT_PATH)

if(NOT JUCE_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        juce
        GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
        GIT_TAG 8.0.0
    )
    FetchContent_MakeAvailable(juce)
endif()

juce_add_plugin(ir-loader-g
    COMPANY_NAME "Minimalist DSP"
    PLUGIN_MANUFACTURER_CODE "MinD"
    PLUGIN_CODE "Irld"
    FORMATS VST3
    PRODUCT_NAME "IR Loader"
)

target_sources(ir-loader-g PRIVATE
    src/processor.cpp
    src/editor.cpp
)

target_compile_features(ir-loader-g PRIVATE cxx_std_20)

target_compile_definitions(ir-loader-g PUBLIC
    JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(ir-loader-g PRIVATE
    juce::juce_audio_utils
    juce::juce_audio_processors
    juce::juce_dsp
    juce::juce_gui_basics
    juce::juce_recommended_config_flags
    juce::juce_recommended_warning_flags
)
