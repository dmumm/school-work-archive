//-------------------------------------------------------
//
//  BasicViewer.C
//
//  This viewer is a wrapper of the Glut calls needed to
//  display opengl data.  Options for zooming,
//  labeling the window frame, etc are available for
//  derived classes to use.
//
//
//  Copyright (c) 2003,2017,2023 Jerry Tessendorf
//
//--------------------------------------------------------


#include "BasicViewer.h"

#include <GL/gl.h> // OpenGL itself.
#include <GL/glu.h> // GLU support library.
#include <GL/glut.h> // GLUT support library.
#include <cmath>
#include <cstring>
#include <iostream>
#include <sstream>

using namespace std;
using namespace image;

namespace viewer {

void cbDisplayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	BasicViewer::Instance()->Display();
	glutSwapBuffers();
}

void cbIdleFunc()
{
	BasicViewer::Instance()->Idle();
}

void cbKeyboardFunc(unsigned char key, int x, int y)
{
	BasicViewer::Instance()->Keyboard(key, x, y);
}

BasicViewer * BasicViewer::pBasicViewer = nullptr;

BasicViewer::BasicViewer()
: initialized(false)
, width(512)
, height(512)
, display_mode(GLUT_DOUBLE | GLUT_RGBA)
, title(string("Image Viewer"))
, mouse_x(0)
, mouse_y(0)
{
	cout << "Display Window Loaded\n";
}

BasicViewer::~BasicViewer() {}

void BasicViewer::Init(StringVector const & args)
{

	int argc = (int)args.size();
	char ** argv = new char *[argc];
	for(int i = 0; i < argc; i++) {
		argv[i] = new char[args[i].length() + 1];
		strcpy(argv[i], args[i].c_str());
	}
	string window_title = title;
	glutInit(&argc, argv);
	glutInitDisplayMode(display_mode);
	glutInitWindowSize(width, height);
	glutCreateWindow(window_title.c_str());
	glClearColor(1.0, .82, 0.7, 0.0);

	glutDisplayFunc(&cbDisplayFunc);
	glutIdleFunc(&cbIdleFunc);
	glutKeyboardFunc(&cbKeyboardFunc);

	initialized = true;
}

void BasicViewer::Init(StringVector const & args, UserInput const details)
{

	int argc = (int)args.size();
	char ** argv = new char *[argc];
	for(int i = 0; i < argc; i++)
	{
		argv[i] = new char[args[i].length() + 1];
		strcpy(argv[i], args[i].c_str());
	}
	string window_title = details.filename;

	glutInit(&argc, argv);
	glutInitDisplayMode(display_mode);
	glutInitWindowSize(details.image.getWidth(), details.image.getHeight());
	glutCreateWindow(window_title.c_str());
	glClearColor(0.5, 0.5, 0.6, 0.0);

	glutDisplayFunc(&cbDisplayFunc);
	glutIdleFunc(&cbIdleFunc);
	glutKeyboardFunc(&cbKeyboardFunc);

	initialized = true;
	cout << "BasicViewer Initialized\n";
}

void BasicViewer::MainLoop()
{
	Usage();
	glutMainLoop();
}

void BasicViewer::Display()
{
	using RawImageValues = float *;

	if(! initialized) {
		cerr << "ERROR: BasicViewer not initialized\n";
		exit(EXIT_FAILURE);
	}

	RawImageValues flippedData = displayedImage.getVerticallyFlippedData();

	switch(displayedImage.getChannelCount()) {

	case 1: {
		cerr << "WARNING: imgviewer does not support 2-channel images!\n";
		glDrawPixels(displayedImage.getWidth(), displayedImage.getHeight(), GL_LUMINANCE, GL_FLOAT, flippedData);
		return;
	}

	case 2: {
		cerr << "WARNING: imgviewer does not support 2-channel images!\n";
		glDrawPixels(displayedImage.getWidth(), displayedImage.getHeight(), GL_LUMINANCE_ALPHA, GL_FLOAT, flippedData);
		return;
	}

	case 3: {
		glDrawPixels(displayedImage.getWidth(), displayedImage.getHeight(), GL_RGB, GL_FLOAT, flippedData);
		return;
	}

	case 4: {
		cerr << "WARNING: imgviewer does not support 4-channel images!\n";
		glDrawPixels(displayedImage.getWidth(), displayedImage.getHeight(), GL_RGBA, GL_FLOAT, flippedData);
		return;
	}
	} // end switch
}

StringVector splitString(string const & input, char const & delimiter)
{
	std::istringstream remaining(input);
	string token = input;
	vector<string> tokens;

	while(getline(remaining, token, delimiter)) {
		tokens.push_back(token);
	}

	return tokens;
}

StringMap supportedFormats()
{
	string formats = OIIO::get_string_attribute("extension_list");
	char const TYPE_DELIMITER = ';';
	char const NAME_DELIMITER = ':';
	char const EXTENSION_DELIMITER = ',';
	StringVector formatSplit = splitString(formats, TYPE_DELIMITER);
	StringMap formatMap;
	for(int i = 0; i < formatSplit.size(); i++)
    {
		StringVector nameAndExtensions = splitString(formatSplit[i], NAME_DELIMITER);
		string formatName = nameAndExtensions[0], // "hdr"
		rawExtensions = nameAndExtensions[1]; // "hdr,rgbe"
		StringVector formatExtensions = splitString(rawExtensions, EXTENSION_DELIMITER);
		for(int j = 0; j < formatExtensions.size(); j++) {
			formatMap.insert({ formatName, formatExtensions[j] });
		}
	}
	return formatMap;
}

void BasicViewer::Keyboard(unsigned char key, int x, int y)
{
	// histogram equalization constants

	int const NUM_BINS = 1000;

	// coherent subtraction constants

	int const SUBTRACT_WITH = 2;
	int const SUBTRACT_FROM = 1;

	// Julia Set Constants

	double const CENTER_X = 0.03811;
	double const CENTER_Y = 0.01329;

	double const ZC_REAL = 0.8 * cos(254.3 * 3.14159265 / 180.0);
	double const ZC_IMAG = 0.8 * sin(254.3 * 3.14159265 / 180.0);
	Point const ZC = { ZC_REAL, ZC_IMAG };


	double const CYCLES = 2;

	// Configurations

	constexpr std::array<double, 3> RANGES = { 1.0, 1.0e-3, 1.0e-6 };
	double const RANGE = RANGES[2];
	constexpr std::array<int, 3> NB_ITERATIONS = { 100, 250, 500 };
	int const NB_ITERATION = NB_ITERATIONS[0];


	switch(key) {
	case 'i': // Fall through to I
	case 'I': {

    	cout << key << ": Applying image differencing...\n" << flush;
		Image tempImage(displayedImage);
		Image requestedImage(displayedImage);
		cout << "Enter image path: ";
		string path;
		cin >> path;
        requestedImage.load(path);
		ImageProcessor::applyImageDifference(displayedImage, requestedImage, tempImage);
		displayedImage = tempImage;
		glutPostRedisplay();
		cout << "done,\n";
		break;
	}
	case 'a': // Fall through to A
	case 'A': {
		vector<Image::Pixel> covariance_matrix = displayedImage.getCovarianceMatrix();
		cout << "Covariance Matrix:\n";
		for(int i = 0; i < covariance_matrix.size(); ++i)
		{
			cout << "Channel " << i << ": ";
			for(int j = 0; j < covariance_matrix[i].size(); ++j)
			{
				cout << covariance_matrix[i][j];
				if(j < covariance_matrix[i].size() - 1) cout << ", ";
			}
			cout << "\n";
		}
		cout << "\n";
		float minimized_variance = displayedImage.calculateA(SUBTRACT_FROM, SUBTRACT_WITH);
		cout << "Minimized Variance: " << minimized_variance << "\n";
		break;
	}
	case 'V': {
		Image::Pixel const BIAS = { 0.1, 0.1, 0.1 };
		Image tempImage(displayedImage);
		cout << "V: Applying bias of {";
		for(int i = 0; i < BIAS.size(); ++i)
		{
			cout << BIAS[i];
			if(i < BIAS.size() - 1) cout << " ";
		}
		cout << "}..." << flush;
		ImageProcessor::applyBias(BIAS, tempImage);
		displayedImage = tempImage;
		glutPostRedisplay();
		cout << "done\n";
		break;
	}
	case 'v': {
		Image::Pixel const BIAS = { -0.1, -0.1, -0.1 };
		Image tempImage(displayedImage);
		cout << "v: Applying bias of {";
		for(int i = 0; i < BIAS.size(); ++i)
		{
			cout << BIAS[i];
			if(i < BIAS.size() - 1) cout << " ";
		}
		cout << "}..." << flush;
		ImageProcessor::applyBias(BIAS, tempImage);
		displayedImage = tempImage;
		glutPostRedisplay();
		cout << "done\n";
		break;
	}
	case 'b': {
		float const BRIGHTNESS_DECREASE = 0.75;
		cout << "b: Brightness multiplier of " << BRIGHTNESS_DECREASE << " applying..." << flush;
		Image tempImage(displayedImage);
		ImageProcessor::applyBrightness(BRIGHTNESS_DECREASE, tempImage);
		displayedImage = tempImage;
		glutPostRedisplay();
		cout << "done\n";
		break;
	}
	case 'B': {
		float const BRIGHTNESS_INCREASE = 1.25;
		cout << "B: Brightness multiplier of " << BRIGHTNESS_INCREASE << " applying..." << flush;
		Image tempImage(displayedImage);
		ImageProcessor::applyBrightness(BRIGHTNESS_INCREASE, tempImage);
		displayedImage = tempImage;
		glutPostRedisplay();
		cout << "done\n";
		break;
	}
	case 'h': // Fall through to H
	case 'H': {
		cout << key << ": Applying histogram equalization..." << flush;
		Image tempImage(displayedImage);
		ImageProcessor::applyHistogramEqualization(NUM_BINS, displayedImage, tempImage);
		displayedImage = tempImage;
		glutPostRedisplay();
		cout << "done,\n";

		break;
	}
	case 'c': // Fall through to C
	case 'C': {
		cout << key << ": Applying contrast standardization..." << flush;
		Image tempImage(displayedImage);
		auto normalization_data = ImageProcessor::applyContrastNormalization(displayedImage, tempImage);
		displayedImage = tempImage;
		glutPostRedisplay();
		cout << "done\n";
		// if(normalization_data.size() == 0){cout << "No normalization data to display!\n";break; }
		if(normalization_data[0][0] == 0)
		{
			cout << "No normalization data to display!\n";
			break;
		}
		cout << "Retrieved normalization data:\n"
		     << flush;
		cout << "Channel Averages: " << normalization_data[0][1] << ", " << normalization_data[0][1] << ", " << normalization_data[0][2] << "\n"
		     << flush;
		cout << "Channel RMS: " << normalization_data[1][0] << ", " << normalization_data[1][1] << ", " << normalization_data[1][2] << "\n";
		break;
	}
	case 'r': // Fall through to R
	case 'R': {
		cout << key << ": Reversing contrast standardization..." << flush;
		Image tempImage(displayedImage);
		if(tempImage.getNormalizationData().size() == 0)
		{
			cout << "\nNo normalization data to reverse!\n";
			break;
		}
		ImageProcessor::reverseContrastNormalization(displayedImage.getNormalizationData(), displayedImage, tempImage);
		displayedImage = tempImage;
		glutPostRedisplay();
		cout << "done\n";
		break;
	}
	case 'J': {
		Point center = { CENTER_X, CENTER_Y };
		JuliaSet juliaWarp(ZC, NB_ITERATION, CYCLES);
		image::ColorLUT colorLUTInstance; // default gamma value
		cout << "Before ApplyFractalWarpLUT:" << endl
		     << "Center: (" << center.x << ", " << center.y << ")" << endl
		     << "Range: " << RANGE << endl;
		ApplyFractalWarpLUT(center, RANGE, juliaWarp, colorLUTInstance, displayedImage); // Or adjust index as needed.
		glutPostRedisplay();
		cout << "Displayed Julia Set\n";
		break;
	}
	case 'j': {
		cout << "Wrote displayed image to file...\t";
		string const base_name = GetTitle();
		string actual_filename;
		displayedImage.writeJPG(base_name, actual_filename);
		cout << actual_filename << "\n";
		break;
	}
	case 'e': // Fall through to O
	case 'E': {
		cout << "Wrote displayed image to file...\t";
		string const base_name = GetTitle();
		string actual_filename;
		displayedImage.writeEXR(base_name, actual_filename);
		cout << actual_filename << "\n";
		break;
	}
	case 't': // Fall through to T
	case 'T': {
		cout << "Wrote displayed image to file...\t";
		string const base_name = GetTitle();
		string actual_filename;
		displayedImage.writeText(base_name, actual_filename);
		cout << actual_filename << "\n";
		break;
	}
	case 'g': {
		float const GAMMA_DECREASE = 0.9;
		cout << "Gamma of " << GAMMA_DECREASE << " applying..." << flush;
		Image tempImage(displayedImage);
		ImageProcessor::applyGamma(GAMMA_DECREASE, tempImage);
		displayedImage = tempImage;
		glutPostRedisplay();
		cout << "done\n";
		break;
	}
	case 'G': {
		float const GAMMA_INCREASE = 1.111111;
		cout << "Gamma of " << GAMMA_INCREASE << " applying..." << flush;
		Image tempImage(displayedImage);
		ImageProcessor::applyGamma(GAMMA_INCREASE, tempImage);
		displayedImage = tempImage;
		glutPostRedisplay();
		cout << "done\n";
		break;
	}
		/* 	case 'n': {
				float const GAMMA_DECREASE = 0.9;

				Image tempImage(displayedImage);
				ImageProcessor::applyNormalizedGamma(GAMMA_DECREASE, tempImage);
				displayedImage = tempImage;

				glutPostRedisplay();
				cout << "Gamma of " << GAMMA_DECREASE << " applied to normalized image\n";
				break;
			}
			case 'N': {
				float const GAMMA_INCREASE = 1.111111;
				Image tempImage(displayedImage);
				ImageProcessor::applyNormalizedGamma(GAMMA_INCREASE, tempImage);
				displayedImage = tempImage;
				glutPostRedisplay();
				cout << "Gamma of " << GAMMA_INCREASE << " applied to normalized image\n";
				break;
			} */
	case 's': {
		cout << "Sharpening...\t" << flush;
		Stencil sharpen;
		Image tempImage;
		sharpen.setToSharpen();
		ImageProcessor::doCircularLinearConvolution(sharpen, displayedImage, tempImage);
		displayedImage = tempImage;
		glutPostRedisplay();
		cout << "done\n";
		break;
	}
	case 'd': {
		cout << "Blurring...\t" << flush;
		Stencil blur;
		Image tempImage;
		blur.setToBlur();
		ImageProcessor::doCircularLinearConvolution(blur, displayedImage, tempImage);
		displayedImage = tempImage;
		glutPostRedisplay();
		cout << "done\n";
		break;
	}
	case 'l': {
		cout << "Bounded Linear Convolution applying..." << flush;
		Stencil myStencil;
		Image tempImage;
		ImageProcessor::doBoundedLinearConvolution(myStencil, displayedImage, tempImage);
		displayedImage = tempImage;
		glutPostRedisplay();
		cout << "done\n";
		break;
	}
	case 'o': {
		cout << "Bounded Linear Convolution applying..." << flush;
		Stencil myStencil;
		Image tempImage;
		ImageProcessor::doCircularLinearConvolution(myStencil, displayedImage, tempImage);
		displayedImage = tempImage;
		glutPostRedisplay();
		cout << "done\n";
		break;
	}
	case '-': {
		cout << "Isolating black values...\t" << flush;
		Image tempImage(displayedImage);
		ImageProcessor::isolateBlacks(displayedImage, tempImage);
		displayedImage = tempImage;
		glutPostRedisplay();
		cout << "done\n";
		break;
	}
	case 27 /* ESC */: {
		// Hide the window
		glutHideWindow();

		// Ask for user confirmation in the terminal
		cout << "Do you really want to exit? (y/n): ";
		char confirm;
		cin >> confirm;

		if(confirm == 'y' || confirm == 'Y')
		{
			cout << "User requested exit...\n";
			exit(EXIT_SUCCESS);
		}
		glutShowWindow();
		break;
	}
	case '2': {
		cout << "Applying coherent subtraction of channel 2 from channel 1..." << flush;
		cout << "RMS: \n";
		cout << "Channel 0: " << displayedImage.getChannelRMSs()[0] << "\n";
		cout << "Channel 1: " << displayedImage.getChannelRMSs()[1] << "\n";
		cout << "Channel 2: " << displayedImage.getChannelRMSs()[2] << "\n";
		Image tempImage(displayedImage);
		ImageProcessor::coherentSubtraction(displayedImage, tempImage, SUBTRACT_FROM, SUBTRACT_WITH);
		displayedImage = tempImage;
		glutPostRedisplay();
		cout << "RMS: \n";
		cout << "Channel 0: " << displayedImage.getChannelRMSs()[0] << "\n";
		cout << "Channel 1: " << displayedImage.getChannelRMSs()[1] << "\n";
		cout << "Channel 2: " << displayedImage.getChannelRMSs()[2] << "\n";
		cout << "done\n";
		break;
	}
	} // end switch
}

void BasicViewer::Idle()
{
}

void BasicViewer::Usage()
{
	cout << "--------------------------------------------------------------\n";
	cout << "BasicViewer usage:\n";
	cout << "--------------------------------------------------------------\n";
	cout << "H      convert to histogram equalization\n";
	cout << "C      convert image to contrast units\n";
	cout << "J      julia set applied\n";
	cout << "j      save current image to jpg\n";
	cout << "E      save current image to exr\n";
	cout << "T      save current image data to text\n";
	cout << "b/B    decreases/increases brightness by 10%\n";
	cout << "v/V    subtracts/adds configured bias\n";
	cout << "g/G    decreases/increases gamma by 10%\n";
	// cout << "n/N    decreases/increases gamma of normalized image by 10% \n";
	cout << "s      sharpens\n";
	cout << "d      blurs\n";
	cout << "l      applies random stencil with bounded linear convolution\n";
	cout << "o      applies random stencil with circular linear convolution\n";
	cout << "-      isolates black values\n";
	cout << "ESC    exit without saving\n";
	cout << "2      apply coherent subtraction of channel 1 from channel 0\n";
	cout << "--------------------------------------------------------------\n";
}

BasicViewer * CreateViewer()
{
	return BasicViewer::Instance();
}

} // namespace viewer
