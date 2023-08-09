double inputLayerWeights[2][1][8] = {{-0.2, 0.3, 0.4, 0.5, 0.6, -0.7, 0.8, -0.9}, // input layer weights
                                     {-0.4, 0.5, 0.6, -0.4, 0.5, 0.6, -0.4, 0.5}};

double layerWeights[5][8][8] = {{-0.2, 0.3, -0.4, 0.5, 0.6, -0.7, 0.8, -0.9,
                                 0.1, 0.9, -0.3, 0.2, -0.5, 0.4, 0.6, -0.8,
                                 -0.7, 0.5, 0.8, -0.2, -0.3, -0.6, 0.1, 0.4,
                                 -0.2, 0.3, -0.4, 0.5, 0.6, -0.7, 0.8, -0.9,
                                 0.1, 0.9, -0.3, 0.2, -0.5, 0.4, 0.6, -0.8,
                                 -0.7, 0.5, 0.8, -0.2, -0.3, -0.6, 0.1, 0.4,
                                 -0.2, 0.3, -0.4, 0.5, 0.6, -0.7, 0.8, -0.9,
                                 0.1, 0.9, -0.3, 0.2, -0.5, 0.4, 0.6, -0.8},
                                {0.2, -0.3, 0.4, -0.5, -0.6, 0.7, -0.8, 0.9,
                                 -0.1, -0.9, 0.3, -0.2, 0.5, -0.4, -0.6, 0.8,
                                 0.7, -0.5, -0.8, 0.2, 0.3, 0.6, -0.1, -0.4,
                                 0.2, -0.3, 0.4, -0.5, -0.6, 0.7, -0.8, 0.9,
                                 -0.1, -0.9, 0.3, -0.2, 0.5, -0.4, -0.6, 0.8,
                                 0.7, -0.5, -0.8, 0.2, 0.3, 0.6, -0.1, -0.4,
                                 0.2, -0.3, 0.4, -0.5, -0.6, 0.7, -0.8, 0.9,
                                 -0.1, -0.9, 0.3, -0.2, 0.5, -0.4, -0.6, 0.8},

                                {0.3, -0.4, 0.5, -0.6, -0.7, 0.8, -0.9, 0.1, -0.2, -0.9, 0.4, -0.3, 0.5, -0.6, -0.8, 0.1, 0.6, -0.5, -0.7, 0.2, 0.4, 0.8, -0.1, -0.3, 0.3, -0.4, 0.5, -0.6, -0.7, 0.8, -0.9, 0.1, -0.2, -0.9, 0.4, -0.3, 0.5, -0.6, -0.8, 0.1, 0.6, -0.5, -0.7, 0.2, 0.4, 0.8, -0.1, -0.3, 0.3, -0.4, 0.5, -0.6, -0.7, 0.8, -0.9, 0.1, -0.2, -0.9, 0.4, -0.3, 0.5, -0.6, -0.8, 0.1},
                                {0.4, -0.5, 0.6, -0.7, -0.8, 0.9, -0.1, 0.2, -0.3, -0.8, 0.5, -0.4, 0.6, -0.7, -0.9, 0.2, 0.5, -0.4, -0.6, 0.3, 0.2, 0.8, -0.2, -0.1, 0.4, -0.5, 0.6, -0.7, -0.8, 0.9, -0.1, 0.2, -0.3, -0.8, 0.5, -0.4, 0.6, -0.7, -0.9, 0.2, 0.5, -0.4, -0.6, 0.3, 0.2, 0.8, -0.2, -0.1, 0.4, -0.5, 0.6, -0.7, -0.8, 0.9, -0.1, 0.2, -0.3, -0.8, 0.5, -0.4, 0.6, -0.7, -0.9, 0.2},
                                {0.5, -0.6, 0.7, -0.8, -0.9, 0.1, -0.2, 0.3, -0.4, -0.7, 0.6, -0.5, 0.8, -0.6, -0.2, 0.1, 0.4, -0.3, -0.5, 0.1, 0.6, 0.7, -0.3, -0.2, 0.5, -0.6, 0.7, -0.8, -0.9, 0.1, -0.2, 0.3, -0.4, -0.7, 0.6, -0.5, 0.8, -0.6, -0.2, 0.1, 0.4, -0.3, -0.5, 0.1, 0.6, 0.7, -0.3, -0.2, 0.5, -0.6, 0.7, -0.8, -0.9, 0.1, -0.2, 0.3, -0.4, -0.7, 0.6, -0.5, 0.8, -0.6, -0.2, 0.1}};

double outputLayer[1][8] = {-0.1, 0.2, 0.3, 0.4, 0.5, -0.6, -0.7, 0.8};
double layersAns[1][8]{0};          // ans of each layer
double inputvalues[2] = {0.1, 0.2}; // starting input values