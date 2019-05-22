# machine-learning
### How to compile:  
#### make install
### How to run:  
#### ./regression   example/Xtrain.txt example/Ytrain.txt example/Xtest.txt  example/Ytest.txt
Program was tested on Graduate admissions dataset  
The dataset contains several parameters which are considered important during the application for Masters Programs.  
The parameters included are : 1. GRE Scores ( out of 340 ) 2. TOEFL Scores ( out of 120 ) 3. University Rating ( out of 5 )  
4. Statement of Purpose and Letter of Recommendation Strength ( out of 5 ) 5. Undergraduate GPA ( out of 10 )  
6. Research Experience ( either 0 or 1 ) 7. Chance of Admit ( ranging from 0 to 1 )  
### Example  
299     102     3       4       3.5     8.62    0  
290     104     4       2       2.5     7.46    0  
296     99      2       3       3.5     7.28    0  
327     104     5       3       3.5     8.84    1  
335     117     5       5       5       9.56    1  
334     119     5       4.5     4.5     9.48    1  
321     109     3       3       3       8.54    1  
315     105     2       2       2.5     7.65    0  
0.56 0.45 0.47 0.71 0.94 0.94 0.79 0.39  
290     100     1       1.5     2       7.56    0  
303     98      1       2       2.5     7.65    0  
326     112     3       3.5     3       9.1     1  
333     118     5       5       5       9.35    1  
339     114     5       4       4.5     9.76    1  
answer:  
0.49 0.66 0.72 0.72 0.86  
right answer:  
0.47 0.56 0.84 0.92 0.96  
