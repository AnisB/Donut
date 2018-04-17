#!/usr/bin/env ruby

# External requirements
require 'fileutils'
require 'optparse'

# option variables
$options = {}
$compiler = ["vc14", "vc15"]
$platform = ["win64"]
$build = ["debug", "release"]

# Build variables
$script_dir = File.expand_path(File.dirname(__FILE__))
$root_build_dir = nil
$cmake_directory =  nil
$output_directory = nil
$platform_name = nil

CMAKE_EXE = "cmake"

def parse_options(argv, options)
	opt_parser = OptionParser.new do|opts|
		opts.banner = "Usage: make.rb [options]"
		opts.on('-c',  '--compiler <compiler>', "Target compiler [#{$compiler.join(", ")}]") { |v| options[:compiler] = v }
		opts.on('-p',  '--platform <platform>', "The target platform [#{$platform.join(", ")}]" ) { |v| options[:platform] = v }
		opts.on('-t', '--tests', "Generate tests for the library (and run them if generated)" ) { |v| options[:tests] = v }
		opts.on('-b', '--build', "Compiles the project in a given build [#{$build.join(", ")}]") { |v| options[:build] = v }
		opts.on('-h',  '--help', "Displays Help") do
			puts opts
			exit 1
		end
	end

	# Parse options
	begin
		opt_parser.parse(argv)
	rescue OptionParser::ParseError => e
		puts e
		puts
		puts opt_parser
		exit 1
	end

	return opt_parser
end

# Setting the default OptionParser
if $options[:compiler] == nil
	$options[:compiler] = "vc15"
end

if $options[:platform] == nil
	$options[:platform] = "win64"
end

if $options[:link_type] == nil
	$options[:link_type] = "mt"
end

if $options[:tests] == nil
	$options[:tests] = true
end

if $options[:build] == nil
	$options[:build] = "release"
end

def create_dir_if_does_not_exist (directory_name)
	Dir.mkdir(directory_name) unless File.exists?(directory_name)
end

# Generate the required directires
def generate_build_directory()
	$script_dir = File.expand_path(File.dirname(__FILE__))
	$platform_name = $options[:compiler] + "_" + $options[:platform]
	$root_build_dir = $script_dir + "/build_" + $platform_name
	$cmake_directory =  $root_build_dir + "/cmake_output"
	$output_directory = $root_build_dir + "/output_dir"

	create_dir_if_does_not_exist($root_build_dir)
	create_dir_if_does_not_exist($cmake_directory)
	create_dir_if_does_not_exist($output_directory)
end

# Functions that generates the generator string based on the compiler and the platform for cmake
def get_generator_name()
	generator = " -G"

	if $options[:compiler] == "vc14"
		generator += "\"Visual Studio 14 2015"
	elsif $options[:compiler] == "vc15"
		generator += "\"Visual Studio 15 2017"
	else
		puts "\nERROR: Compiler '#{$options[:compiler]}' not recognized."
		exit 1
	end
	
	if $options[:platform] == "win64"
		generator += " Win64\" "
	else
		puts "\nERROR: Architecture not recognized '#{$options[:platform]}' not recognized."
		exit 1
	end

	return generator
end

# String that defines the platform name that we will be compiling for (unique according to the target compiler/linktype/platform)
def get_platform_name()
	return " -DBENTO_PLATFORM_NAME=" + $platform_name
end

def get_output_dir_name()
	return " -DBENTO_OUTPUTDIR=" + $output_directory
end

# For a given setup, generates projects and compiles the library
def generate_project()
	# Move into the cmake_directory if possible
	Dir.chdir($cmake_directory) do
		# We need to build the cmake command
		command = CMAKE_EXE + " ../.."
		# Get the generator name
		command += get_generator_name()
		# Inject the platfom name
		command += get_platform_name()
		# Inject the platfom name
		command += get_output_dir_name()

		# Execute the cmake command
		if !system(command)
			puts("CMake generation failed")
			exit 1
		else
			puts("cmake project generated")
		end
	end
end

def compile_engine()
	Dir.chdir($cmake_directory) do
		# Compile the project in release mode
		if $options[:build] == "release"
			if !system(CMAKE_EXE + " --build . --config Release")
				exit 1
			end
		elsif $options[:build] == "debug"
			if !system(CMAKE_EXE + " --build . --config Debug")
				exit 1
			end
		end
	end
end

# Parse the options that have been fed in the command line
parse_options(ARGV, $options)

# Generate the directory names
generate_build_directory()

# Generate the project
generate_project()

# Compile the engine
compile_engine()