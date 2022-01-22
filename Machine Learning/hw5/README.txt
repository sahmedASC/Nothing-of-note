Name: Saaif Ahmed
RIN: 661925946
Email & RCSID: ahmeds7@rpi.edu

Instructions for Running main.py:

    	main.py uses the pandas, numpy, openpyxl, random, and matplotlib python libraries. These should all be installed
    	to your python interpreter before running.

    	Ensure that main.py is in the same directory as the .csv files representing the data.
	
	Pass in command line arguments to file when running
	
	An example line that can be run is

	$python mysgdsvm.py MNIST-13.csv 10 3
	
	And the code will output the data into a tmp.csv and it will
	also output the avg time and stdev of the time of the number of runs.

Summary:
	This main file has input: (1) a filename containing the dataset, (2) minibatch
	size, and (3) the number of runs, and output: (1) the average runtime and standard
	deviations printed to the terminal (stdout).

Assumptions:
	The input is always good.
	The file is always made well.
	The first column of the file is the label or target
	The remaining columns are the features.
	Filename extension is (.csv) is needed.
	Filename should be of the .csv type.

