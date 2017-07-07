#!/usr/bin/env ruby

# External requirements
require 'fileutils'
require 'optparse'

# option variables
$options = {}
$compiler = ["vc14"]
$platform = ["win64"]

# Build variables
$script_dir = File.expand_path(File.dirname(__FILE__))
$platform_name =  nil
$build_directory = nil

CMAKE_EXE = "cmake"

def parse_options(argv, options)
	opt_parser = OptionParser.new do|opts|
		opts.banner = "Usage: make.rb [options]"
		opts.on('-c',  '--compiler <compiler>', "Target compiler [#{$compiler.join(", ")}]") { |v| options[:compiler] = v }
		opts.on('-p',  '--platform <platform>', "The target platform [#{$platform.join(", ")}]" ) { |v| options[:platform] = v }
		opts.on('-t', '--tests', "Generate tests for the library (and run them if generated)" ) { |v| options[:tests] = v }
		opts.on('-d', '--debug_build', 'Compiles the project in a debug build') { options[:debug_build] = true }
		opts.on('-r', '--release_build', 'Compiles the project in a release build') { options[:release_build] = true }
		opts.on('-h',  '--help', 'Displays Help') do
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
	$options[:compiler] = "vc14"
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

if $options[:debug_build] == nil
	$options[:debug_build] = true
end

if $options[:release_build] == nil
	$options[:release_build] = true
end


def create_dir_if_does_not_exist (directory_name)
	Dir.mkdir(directory_name) unless File.exists?(directory_name)
end

# Generate the required directires
def generate_build_directory()
	# Generate the platform name
	$platform_name = $options[:compiler] + "_" + $options[:platform]
	# Generate the build directory name
	$build_directory = "build_" + $platform_name
end

# Functions that generates the generator string based on the compiler and the platform for cmake
def get_generator_name()
	generator = " -G"

	if $options[:compiler] == "vc14"
		generator += "\"Visual Studio 14 2015"
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
	return " -DPLATFORM_NAME=" + $platform_name
end

# Function that evaluates if tests are generated (only applicable to windows for the moment)
def get_test_flag()
	tests = ""

	if $options[:tests] == true
		tests = " -DTESTS=TRUE"
	else
		tests = " -DTESTS=FALSE"
	end

	return tests
end

# For a given setup, generates projects and compiles the library
def generate_project()
	# Create the build folder
	create_dir_if_does_not_exist($build_directory)

	# Move into the build build_directory if possible
	Dir.chdir($build_directory) do
		# We need to build the cmake command
		command = CMAKE_EXE + " .."
		# Get the generator name
		command += get_generator_name()
		# Shall the tests be generated ?
		command += get_test_flag()
		# Inject the platfomr name
		command += get_platform_name()

		# Execute the cmake command
		if !system(command)
			puts("CMake generation failed")
			exit 1
		else
			puts("cmake project generated")
		end
	end
end

def compile_project()
	Dir.chdir($build_directory) do
		# Compile the project in release mode
		if $options[:release_build]
			if !system(CMAKE_EXE + " --build . --config Release")
				exit 1
			end
		end

		# Compile the project in debug mode
		if $options[:debug_build]
			if !system(CMAKE_EXE + " --build . --config Debug")
				exit 1
			end
		end
	end
end

parse_options(ARGV, $options)

# Generate the directory names
generate_build_directory()

# Generate the project
generate_project()

# Compile the project
compile_project()