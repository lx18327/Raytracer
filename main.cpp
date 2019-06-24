#include <iostream>
#include "scenes.h"

using namespace std;

void InputErrorReporter(int errorInput)
{
	system("cls");

	switch (errorInput)
	{
	case 1:
		std::cout << "ERROR : Please Enter Valid Image Width.\n" << std::endl;
		break;
	case 2:
		std::cout << "ERROR : Please Enter Valid Image Height.\n" << std::endl;
		break;
	case 3:
		std::cout << "ERROR : Please Enter Valid Ray Samples.\n" << std::endl;
		break;
	case 4:
		std::cout << "ERROR : Please Enter Valid Output Image Name.\n" << std::endl;
		break;
	case 5:
		std::cout << "ERROR : Please Select The Valid Scene Index.\n" << std::endl;
		break;
	}
}


// Application Entry Point
int main(int argc, char* argv[])
{
	int imageWidth = 0;
	int imageHight = 0;
	int raySamples = 0;
	std::string outputImageName = "";
	int SelectedScene = 0;

	/* Input Test Supported Variables*/
	struct stat info;
	int error = 0;
	int  active_loop = 0;
	char keyboardInput = ' ';
	do
	{
		error = 0;
		active_loop = 0;
		std::cout << "***************************" << std::endl;
		std::cout << "    Welcome To Raytracer" << std::endl;
		std::cout << "***************************" << std::endl;

		try
		{
			std::cout << "Enter Render Image Width (int): ";
			std::cin >> imageWidth;
			if (int(imageWidth) <= 0)
				throw 1;

			std::cout << "Enter Render Image Hight (int): ";
			std::cin >> imageHight;
			if (int(imageHight) <= 0)
				throw 2;

			std::cout << "Enter Render Ray Samples (int): ";
			std::cin >> raySamples;
			if (int(raySamples) <= 0)
				throw 3;

			std::cout << "Enter Output Image Name (Without extension) (string): ";
			std::cin >> outputImageName;
			if (size(outputImageName) <= 0)
				throw 4;

			std::cout << "\nAvailable Scenes Of Cornell-Box" << std::endl;
			std::cout << "*******************************" << std::endl;
			std::cout << "1 : Tracing Light Ray" << std::endl;
			std::cout << "2 : Direct Lighting in Grayscale" << std::endl;
			std::cout << "3 : Direct Lighting in Color" << std::endl;
			std::cout << "Scene To Render (Choose One From Above Index) (int): ";
			std::cin >> SelectedScene;
			if ((SelectedScene < 1) || (SelectedScene > 3))
				throw 5;
		}
		catch (int err)
		{
			InputErrorReporter(err);
			error = 1;
			active_loop = 1;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Do you want to continue? (y/n) : ";
			std::cin >> keyboardInput;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			if (keyboardInput == 'y')
			{
				system("cls");
				continue;
			}
			else
			{
				break;
			}
		}

	} while (active_loop);

	// On Error
	if (error == 1)
		return 1;

	// On Success
	switch (SelectedScene)
	{
	case 1:
		cornell_box_constant_render_scene(imageWidth, imageHight, raySamples, outputImageName);
		break;
	case 2:
		break;
	case 3:
		break;
	}

	std::cout << "\n" << std::endl;
	system("pause");
	return 0;
}