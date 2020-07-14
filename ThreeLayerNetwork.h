#pragma once

#include "Connection.h"
#include "Neuron.h"

// Enumeration for network encoding types:
// - div+divdot
// - div place cells
// - div+divdot, but div setpoint subtracted
typedef enum EncodingType { BOTH, ERROR } EncodingType;

// Enumeration for network decoding types:
// - actions weighted by trace
typedef enum DecodingType { WEIGHTED } DecodingType;

// Struct that defines a network of three spiking layers
typedef struct Network {
  // Encoding type
  EncodingType enc_type;
  // Decoding type
  DecodingType dec_type;
  // D setpoint
  float setpoint;
  // Decoding action vector
  float* actions;
  // Input, encoded input, hidden1, hidden2 and output layer sizes
  int in_size, in_enc_size, hid1_size, hid2_size, out_size;
  // Two input place holders: one for scalar values
  // and one for encoded currents (size in_size)
  float *in, *in_enc;
  // Connection input -> hidden1
  Connection *inhid1;
  // Hidden1 neurons
  Neuron *hid1;
  // Connection hidden1 -> hidden2
  Connection *hid1hid2;
  // Hidden2 neurons
  Neuron *hid2;
  // Connection hidden2 -> output
  Connection *hid2out;
  // Output neurons
  Neuron *out;
} Network;

// Struct that holds the configuration of a three-layer network
// To be used when loading parameters from a header file
typedef struct NetworkConf {
  // Encoding type
  EncodingType const enc_type;
  // Decoding type
  DecodingType const dec_type;
  // D setpoint
  float setpoint;
  // Decoding action vector (just BS if we don't use them)
  float const *actions;
  // Input, encoded input, hidden1, hidden2 and output layer sizes
  int const in_size, in_enc_size, hid1_size, hid2_size, out_size;
  // Connection input -> hidden1
  ConnectionConf const *inhid1;
  // Hidden1 neurons
  NeuronConf const *hid1;
  // Connection hidden1 -> hidden2
  ConnectionConf const *hid1hid2;
  // Hidden2 neurons
  NeuronConf const *hid2;
  // Connection hidden2 -> output
  ConnectionConf const *hid2out;
  // Output neurons
  NeuronConf const *out;
} NetworkConf;

// Build network: calls build functions for children
Network build_network(int const in_size, int const in_enc_size,
                      int const hid1_size, int const hid2_size, int const out_size);

// Init network: calls init functions for children
void init_network(Network *net);

// Reset network: calls reset functions for children
void reset_network(Network *net);

// Load parameters for network from header file and call load functions for
// children
void load_network_from_header(Network *net, NetworkConf const *conf);

// Free allocated memory for network and call free functions for children
void free_network(Network *net);

// Print network parameters (for debugging purposes)
void print_network(Network const *net);

// Forward network and call forward functions for children
// Encoding and decoding inside
float forward_network(Network *net);
