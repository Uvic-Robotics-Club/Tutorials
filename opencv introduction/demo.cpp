#include "demo.h"

int main() {
	// Set up the system default webcam. You can use a different number if you have more than one webcam
	VideoCapture cam(0);

	int counter = 0;
	while (counter < 10) {
		// Get the most recent image from the webcam.
		// Note that for many opencv functions, the result is stored in a Mat object that is passed in as a parameter
		// Mat objects are largely self-managed (including cleanup), avoiding many of C++'s pointer woes
		// Each Mat ("matrix") object typically represents an image, but technically they are generic matrices and can be treated as such
		Mat frame;
		cam.read(frame);
		// If there isn't a new image yet, the variable frame will be empty. Keep trying until there is a new image
		while (frame.empty())
			cam.read(frame);

		do_something(frame);

		// This is a basic way to record a series of images.
		// These images can be later loaded using "Mat src = imload("<path of image>)"
		imwrite("C:/Workspace/" + std::to_string(counter) + std::string(".jpg"), frame);

		counter++;
	}
	return 0;
}

// Does some demo processing on the image and displays it.
// Remember that since we're providing an object, do_something should avoid editingthe src.
void do_something(Mat src) {
	// Displays the matrix "src" in a window named "Source"
	// Defaults to an rgb representation, so some matrixes that don't represent rgb or b&w may look strange
	imshow("Source", src);

	Mat blurred;
	// many opencv functions follow this pattern: src matrix, destination matrix, additionall parameters
	// many of these do not change the source matrix, so it is safe to use it directly
	// This is a strong blur, but used for demonstrational purposes
	GaussianBlur(src, blurred, Size(15, 15), 0);

	// You can have as many of these windows as you want
	imshow("Blurred", blurred);

	add_line(src);

	// Waits at least the specified number of milliseconds, or until any key is pressed.
	// '0' is a special value for "no maximum wait time"
	// Whenever you use an imshow, it won't be updated until the program encounters a "waitKey" call
	waitKey(0);
}

// Adds a horizontal black line to the image
// Represents how to do custom work
void add_line(Mat src) {
	// We're using a custom algorithm here. Don't forget to not mess with the src Matrix!
	Mat marked = src.clone();

	int y = src.size().height / 4;
	// Getting a row vector is the most efficient way to access Mat objects due to caching behaviour
	// You can also do random accesses using "matrix.at<int>(y, x)". Note that the "y" comes before the "x"!
	// Also note that (0, 0) represents the *top left* corner of the image
	Vec3b * row = marked.ptr<Vec3b>(y);
	for (int i = 0; i < marked.size().width; i++) {
		// "Vec3b" is a vector of 3 uchars. By default rgb, each corresponds to a colour channel, but it can represent whatever you want
		row[i] = Vec3b(0, 0, 0);
	}
	// Note that this will only be shown to the user once a "waitKey" call is run.
	// If you wanted to display this immediately without blocking the program, you can use "waitKey(1);"
	imshow("Picture with a line", marked);
}
