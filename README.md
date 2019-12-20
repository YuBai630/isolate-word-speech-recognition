# isolate-word-speech-recognition
DTW algorithm is used to realize template matching so as to recognize isolated words.
This is the speech assignment for the multimedia technology experiment course at northwestern polytechnical university in 2019 autumn semester.

It is divided into two parts: basic experiment and extended experiment.

The basic experient requires us to simply implement the speech recognition system of the 10 digits of 0-9 for isolated words.
It requires us to record the 10 digits 0-9 one time each as a template, and then record the 10 digits 0-9 four times each as test audio.
Then we need to extract MFCC features of audio files and generate .mfc feature files with the tool HCopy.
Next we need to use the Dynamic Time Warping algorithm to match the test data with the template,and the recognition results of the test data are obtained and evaluated.

The extended experient requires us to use more data,the data includes the train set(isolated_digits_ti_train_endpt) and the test set(isolated_digits_ti_test_endpt).
Among them, train sets 38 males and 57 females;test set: 56 men and 57 women.Each speaker recorded eleven values of 1,2,3,4,5,6,7,8,9, O, zero and read each number twice. 
Instead of having a template for each of the preceding numbers, this time the number of templates to choose from has been significantly increased.
I used two ways to get the template. 
The first way is average all the templates;The second way is keep all templates directly.

PS:About the use of HCopy command format is "HCopy –C config_MFCC.cfg –S audios.scp" 
Where -c represents the read configuration (config) file config_mfc.cfg, and -s represents the read list file audios.scp.
The configuration file config_mfc.cfg sets parameters for the MFCC features to be extracted.
The list file shows the path of the audio file to extract features and the path to store the acquired features. 
Each line of the file has the following form:
The path to the audio file[\t]mfc feature file storage path[\t]
For example: audio\0_template.wav mfc\0_template.mfc audio\1template.wav mfc\1_template.mfc

Example of feature extraction process: create two folders audio and MFC in the same level path of HCopy, 
copy all wav audio files into the audio folder, edit the list file audios. SCP, enter the path of HCopy from the command line, 
call HCopy, and get the . MFC feature files corresponding to audio files under the MFC folder.
