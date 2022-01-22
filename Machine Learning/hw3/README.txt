Name: Saaif Ahmed
RIN: 661925946
Email & RCSID: ahmeds7@rpi.edu

Instructions for Running main.py:
    main.py is built as a module file. You can import this file into any other
    python file. You can call the function from the module, pass in the arguments
    and main.py will ouput to the terminal via print().

    main.py uses the pandas, numpy, openpyxl, random, and matplotlib python libraries. These should all be installed
    to your python interpreter before running.

    Ensure that main.py is in the same directory as the python file it is
    being imported into. In addition to the .csv files representing the data.

    For example a file could look like.

import main.py as m
#unccomment either line
#m.naiveBayesGaussian("file.csv",num_splits,vector_of_percent)
#m.logisticRegression("file.csv",num_splits,vector_of_percent)
	You can also directly compile the main.py file and if needed edit the lines 245 and 246
	in any text editor to match the desired run condition.

Other details:
For the homwork the entire spambase.csv was used
A given feature vector x was in R^57
The entries of the feature vector were continuous real values.
The last column was the target column vector y which was binary [0,1]
The number of classes that can be extracted are 2. One for each binary classification ([0,1]).
There were 4601 data entries leaving it the entire input dataset to be R^(4601x57)
and the output vector was in R^(4601x1)
The number of data points was 4601x58.
The code does run quite slow.

