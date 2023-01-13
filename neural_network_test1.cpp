#include <iostream>
#include <vector>
#include <cmath>
#include <random>

// Helper function to calculate sigmoid activation
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

class NeuralNetwork {
public:
    NeuralNetwork(std::vector<int> layerSizes) {
        // Initialize random number generator
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<> dist(0, 1);

        // Create weight matrices for each layer
        for (int i = 0; i < layerSizes.size() - 1; i++) {
            int rows = layerSizes[i];
            int cols = layerSizes[i + 1];
            std::vector<std::vector<double>> weights(rows, std::vector<double>(cols));
            for (int j = 0; j < rows; j++) {
                for (int k = 0; k < cols; k++) {
                    weights[j][k] = dist(gen);
                }
            }
            this->weights.push_back(weights);
        }
    }

    std::vector<double> predict(std::vector<double> input) {
        std::vector<double> output = input;
        for (int i = 0; i < this->weights.size(); i++) {
            output = this->feedforward(output, this->weights[i]);
        }
        return output;
    }

    void train(std::vector<std::vector<double>> input, std::vector<std::vector<double>> target, double learning_rate) {
        // Perform forward propagation
        std::vector<std::vector<double>> activations;
        activations.push_back(input);
        for (int i = 0; i < this->weights.size(); i++) {
            std::vector<double> output = this->feedforward(activations.back(), this->weights[i]);
            activations.push_back(output);
        }

        // Perform backward propagation
        std::vector<std::vector<double>> delta = this->backpropagation(activations.back(), target);
        for (int i = this->weights.size() - 1; i >= 0; i--) {
            std::vector<std::vector<double>> gradient = this->gradient(activations[i], delta);
            this->weights[i] = this->updateWeights(this->weights[i], gradient, learning_rate);
            delta = this->backpropagation(activations[i], delta, this->weights[i]);
        }
    }

private:
    std::vector<std::vector<std::vector<double>>> weights;

    std::vector<double> feedforward(std::vector<double> input, std::vector<std::vector<double>> weights) {
        std::vector<double> output(weights[0].size());
        for (int i = 0; i < weights.size(); i++) {
            for (int j = 0; j < weights[0].size();
