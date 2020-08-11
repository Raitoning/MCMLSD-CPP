#ifndef _LIKELIHOOD_MODEL_H_
#define _LIKELIHOOD_MODEL_H_

#include <string>
#include <vector>

struct LikelihoodModel
{
    std::vector<double> ang_dev_off_hist;
    std::vector<double> ang_dev_on_hist;
    std::vector<double> exist_edge_off;
    std::vector<double> exist_edge_on;
    std::vector<double> length_prior;
    std::vector<double> lengths_off;
    std::vector<double> lengths_on;
    std::vector<double> nexist_edge_off;
    std::vector<double> nexist_edge_on;
};


LikelihoodModel LoadModel (const std::string folderName);


void LoadFile (std::string fileName, std::vector<double> &container);


#endif
