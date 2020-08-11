#include "LikelihoodModel.hpp"

#include <iostream>
#include <fstream>

#include <Instrumentor.h>

LikelihoodModel LoadModel (const std::string folderName)
{
    PROFILE_FUNCTION();

    LikelihoodModel model;

    LoadFile (folderName + "ang_dev_off_hist.txt", model.ang_dev_off_hist);
    LoadFile (folderName + "ang_dev_on_hist.txt", model.ang_dev_on_hist);

    LoadFile (folderName + "exist_edge_off.txt", model.exist_edge_off);
    LoadFile (folderName + "exist_edge_on.txt", model.exist_edge_on);

    LoadFile (folderName + "length_prior.txt", model.length_prior);

    LoadFile (folderName + "lengths_off.txt", model.lengths_off);
    LoadFile (folderName + "lengths_on.txt", model.lengths_on);

    LoadFile (folderName + "nexist_edge_off.txt", model.nexist_edge_off);
    LoadFile (folderName + "nexist_edge_on.txt", model.nexist_edge_on);

    return model;
}


void LoadFile (const std::string fileName, std::vector<double> & container)
{
    PROFILE_FUNCTION();

    std::fstream file (fileName);

    if (file.is_open())
    {
        std::string value;
        bool reading = true;

        while (reading)
        {
            file >> value;

            container.emplace_back (std::stod (value));

            reading = !file.eof();
        }
    }
    else
    {
        std::cerr << "Couldn't open the " << fileName << " file." << std::endl;
        exit (EXIT_FAILURE);
    }
}
