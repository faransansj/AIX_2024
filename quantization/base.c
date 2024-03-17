void do_quantization(network net) {
    int counter = 0;

    int j;
    //Dummy weight_quantization 
#define TOTAL_CALIB_LAYER 11
// TODO
//{{{		

    float input_quant_multiplier[TOTAL_CALIB_LAYER] = {
     128,	  //conv 0
      16,     //conv 2
      16,     //conv 4
      16,     //conv 6
      16,     //conv 8
      16,     //conv 10     
      16,     //conv 12
      16,     //conv 13
      16,     //conv 14
      16,     //conv 17
      16 };    //conv 20

    printf("Multipler    Input    Weight    Bias\n");
    for (j = 0; j < net.n; ++j) {
        layer* l = &net.layers[j];

        /*
        TODO: implement quantization
        The implementation given below is a naive version of per-network quantization; implement your own quantization that minimizes the mAP degradation
        */

        //printf("\n");
        if (l->type == CONVOLUTIONAL) { // Quantize conv layer only            
            size_t const filter_size = l->size * l->size * l->c;

            float weight_scale = compute_weight_scale(l);

            int i, fil;

            // Quantized Parameters
            //{{{
                // Input feature map
            l->input_quant_multiplier = (counter < TOTAL_CALIB_LAYER) ? input_quant_multiplier[counter] : 16;

            // Weight
            l->weights_quant_multiplier = (counter < TOTAL_CALIB_LAYER) ? weight_scale : 16;

            ++counter;
            //}}}	
            // Weight Quantization
            for (fil = 0; fil < l->n; ++fil) {          // 
                for (i = 0; i < filter_size; ++i) {
                    float w = l->weights[fil * filter_size + i] * l->weights_quant_multiplier; // Scale
                    l->weights_int8[fil * filter_size + i] = max_abs(w, MAX_VAL_8); // Clip
                }
            }

            // Bias Quantization
            float biases_multiplier = (l->weights_quant_multiplier * l->input_quant_multiplier);
            for (fil = 0; fil < l->n; ++fil) {
                float b = l->biases[fil] * biases_multiplier; // Scale
                l->biases_quant[fil] = max_abs(b, MAX_VAL_16); // Clip
            }

            //printf(" CONV%d multipliers: input %g, weights %g, bias %g \n", j, l->input_quant_multiplier, l->weights_quant_multiplier, biases_multiplier);
            printf(" CONV%d: \t%g \t%g \t%g \n", j, l->input_quant_multiplier, l->weights_quant_multiplier, biases_multiplier);
        }
        else {
            //printf(" No quantization for layer %d (layer type: %d) \n", j, l->type);
        }
    }
}


float compute_weight_scale(layer* l) {
    float min_val = INFINITY;
    float max_val = -INFINITY;

    size_t const filter_size = l->size * l->size * l->c;

    int fil, i;

    for (fil = 0; fil < l->n; ++fil) {         
        for (i = 0; i < filter_size; ++i) {
            if (l->weights[fil * filter_size + i] < min_val) {
                min_val = l->weights[fil * filter_size + i];
            }
            if (l->weights[fil * filter_size + i] > max_val) {
                max_val = l->weights[fil * filter_size + i];
            }
            
        }
    }

    // Compute weight scale
    float weight_scale = (MAX_VAL_8 - 1) / (max_val - min_val);

    return weight_scale;
}
