#include "opencv2\opencv.hpp"
// Be careful using multiple namespaces - in particular, there is both a std::string and a cv::string.
// For club opencv things, we'll use the cv namespace
using namespace cv;

// C++ is a one-pass compiler, so we need to declare methods that are referenced before the compiler gets to them
void basic_image_manipulation(Mat);
void masking_demo(Mat);
void video_test();

int main() {
	// Loads an image, and stores it in a 'Mat' object
	// Mats are opencv's basic image format, and can be thought of as a multi-dimensional array
	// black-and-white images are 2d arrays, while colour images are 3d arrays
	// Note: they are indexed ***y, x***, with 0, 0 being the top left corner; this is to keep it consistent with matrix notation
	// Note 2: the standard color format is **BGR**, NOT RGB. Watch for this!

	// TODO: replace this image path with an image path on your machine. Note that even in windows, the path uses forward slashes.
	Mat sampleImage = imread("C:/Users/grego/Downloads/monster-image-set-30-fps.tar/monster-image-set-30-fps/raw-001622.jpg");

	basic_image_manipulation(sampleImage);

	masking_demo(sampleImage);
	
	// video_test();
	return 0;
}


void basic_image_manipulation(Mat image) {
	// This creates a window with the name "Source window". We can later reference this window from anywhere
	// WINDOW_AUTOSIZE sets the window to whatever size
	namedWindow("Source window", WINDOW_AUTOSIZE);

	// Take our image 'image', and display it in the window 'Source window'
	imshow("Source window", image);

	// Wait for a keypress before continuing. This is used after 'imshow' calls to allow opencv to display the image
	// The number in brackets is the maximum wait time. '0' corresponds to 'no limit'
	waitKey(0);

	// A lot of opencv functions take the output matrix as a parameter, so we initialize it first
	Mat flipped;
	// flips the image. Parameters: source, destination, dimension to flip.
	// Note that src and dst are common shortforms for source and destination
	flip(image, flipped, 1);

	// Display our flipped image in the same window. This will change what our window is displaying
	imshow("Source window", flipped);
	waitKey(0);

	// Convert our image to a greyscale one and display it
	Mat grey;
	cvtColor(image, grey, COLOR_BGR2GRAY);
	// Create a new window for our greyscale image. We can have as many named windows as we want.
	namedWindow("Window 2", WINDOW_AUTOSIZE);
	imshow("Window 2", grey);
	waitKey(0);
}


void masking_demo(Mat img) {
	// Some (but not all) blurs only make sense on greyscale images. Using them on colour can create new colours with weird effects
	Mat grey;
	cvtColor(img, grey, COLOR_BGR2GRAY);


	// Blurs are common preprocess steps to reduce noise in an image. Different blurs emphasize different things

	// Gaussian blurs are commonly used since they are quick to compute. However, they blend edges quite a bit too
	Mat gaussianBlurred;
	blur(grey, gaussianBlurred, Size(10, 10));
	GaussianBlur(grey, gaussianBlurred, Size(5, 5), 0, 0);
	namedWindow("Gaussian Blurred", WINDOW_AUTOSIZE);
	imshow("Gaussian Blurred", gaussianBlurred);

	// Median blurrs are good at clearing noise while preserving strong edges. Notice the missing small details in the displayed image,
	// but that the track lines are clearly visible.
	// However, they are non-linear (resulting in lost information), and are expensive to compute with a large kernel
	Mat medianBlurred;
	medianBlur(grey, medianBlurred, 5);
	namedWindow("Median Blurred", WINDOW_AUTOSIZE);
	imshow("Median Blurred", medianBlurred);
	waitKey(0);

	// Although not implemented here, Bilateral filters are another filter for emphasizing edges.

	// Add a thresholding operation here

}


// TODO: use QR_Detector as the baseline for putting some webcam tests here.
void video_test() {
	// Set up the system default webcam (the '0' in the constructor)
	// Should be cross-platform
	VideoCapture cam(0);
}
