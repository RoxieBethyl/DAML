#### Author: Blythe Fernandes

# Data Analysis and Machine Learning

#### Done in year 2023-24

This in repository are the projects and exercises done during this course. All the code in this repository is mainly `Python` with a few files in `C++`. A brief discription of the main projects done in during this course are listed under [Project Summaries](#project-summaries).

## Project Summaries

### [Project 1](https://github.com/RoxieBethyl/DAML/tree/main/Sem%201/Project%201): Parameter Estimation with Monte-Carlo Simulations and MINUIT
- Generated synthetic datasets using Monte-Carlo simulations to simulate decay events, producing 10,000 sets of time values based on a predefined probability density function (PDF).
- Applied MINUIT fitting to all 10,000 datasets to estimate parameters.
- Analyzed the datasets to identify and estimate biases from unaccounted background noise, distinguishing between signal events and noise.
- Generated new datasets with defined signal-to-noise ratios and performed parameter estimation fits on these datasets.
- Evaluated trends in the parameters across different simulations to assess the stability and accuracy of the fits.


### **[Project 2](https://github.com/RoxieBethyl/DAML/tree/main/Sem%202/Project%202): Anomaly Detection in Particle Physics using Machine Learning**
- Analyzed the existing dataset derived from the standard model, employing visual descriptors such as plots to gain insights.

- Developed a neural network (NN) using TensorFlow and Scikit-Learn, designed as a Variational Autoencoder (VAE), to enhance understanding of particle data according to the standard model.

- Trained the model to detect "new" reactions within a novel dataset, aiming to identify particles not accounted for by the standard model through anomaly detection.

- Evaluated the trained model by examining the reconstruction loss, which aids in isolating anomaly particles.


### **[Project 4](https://github.com/RoxieBethyl/DAML/tree/main/Sem%202/Project4): Exotic Searching with ATLAS data and ML Classification**
- Hypothesis testing is employed to apply selection cuts on the datasets, enhancing data quality for analysis.
- Kinematic cuts are implemented, filtering the dataset based on the importance of variables, to isolate relevant features.
- Signal and background spectrums are modeled using dedicated functions, facilitating a clearer distinction between the two.
- Parameter fitting focuses on the signal-only spectrum, with statistical significance assessed for the joint mass spectrum to ensure robustness.
- The dataset undergoes training to classify between signal and background, utilizing neural network (NN) training techniques for improved accuracy.
- A brief exploration of search sensitivity's impact is conducted, assessing how it influences the overall detection capability.


## Exercises

Some of the exercises in this repo focus on the ML implementation for efficent data analysis and to understand how to build robust models for training.