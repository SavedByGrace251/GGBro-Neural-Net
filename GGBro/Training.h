//	Authors: Jay Byam, Jonathan Newell
//
//  Training.h
//  GGBro
//

#ifndef Training_h
#define Training_h

#include "Tournament.h"
#include <fstream>
#include <string>
using namespace std;

class Training {
public:
	vector<AI> population;
	Clock trainTimer;
	int generation = 1;
	string saveLocation;
	int saveInterval = 50;
	bool saveGen = false;

	// default ctor
	Training() {}

	// secondary ctor
	Training(int populationSize) {
		setupTraining(populationSize);
	}

	// Setup Training
	//	Setup training
	void setupTraining(int populationSize) {
		population = vector<AI>(populationSize);
	}

	void setMaxTime(int week, int day, int hour, int minute, int seconds) {
		int minutes = 60 * minute;
		int hours = 3600 * hour;
		int days = 86400 * day;
		int weeks = 604800 * week;
		trainTimer.maxtime = weeks + days + hours + minutes + seconds;
	}

	// Train
	//	Commence training
	void train() {
		// validate training can begin
		if (population.size() < 2) {
			throw std::logic_error("The population size is not sufficient to start training.");
		}
		if (trainTimer.maxtime < 1) {
			throw std::logic_error("The training timer is not set.");
		}
		// start training
		trainTimer.start = high_resolution_clock::now();
		while (duration<double>(high_resolution_clock::now() - trainTimer.start).count() < trainTimer.maxtime) {
			cout << "Training generation " << generation << endl;
			if (generation % saveInterval == 0 && !saveGen) {
				save();
			} else {
				saveGen = false;
			}
			// setup tournament
			Tournament tourney(population);

			// run and time tourney
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			tourney.commence();
			double tourneyLength = duration<double>(high_resolution_clock::now() - t1).count();
			cout << "\t| Tournamnet length: " << tourneyLength << endl;

			// Save Tourney information 
			stringstream gen;
			gen << generation;
			ofstream outFile("tournament_info/tourney_" + gen.str() + "_info.data");
			tourney.printStats(outFile);

			// rate the population based on the last tounament
			ratePopulation(tourney);
			// evolve the population
			evolve();
			++generation;
		}
		save();
	}

	// Rate Population
	//	rates the current population based on the given tournament
	void ratePopulation(Tournament& t) {
		int popSize = population.size();
		for (int i = 0; i < popSize; i++) {
			population[i].score = (double) t.scores[i] / t.gamesPlayed[i];
		}
	}

	// Evolve
	//	culls the lower half of the population based on score
	//	and fills the population with new AI
	void evolve() {
		sort(population.begin(), population.end());
		reverse(population.begin(), population.end());
		int halfIdx = population.size() / 2;
		// decide number of AI to splice and evolve
		int nSplice = halfIdx * 0.3;
		int nEvolve = halfIdx - nSplice;

		uniform_int_distribution<int> randomIdx(0, halfIdx - 1);
		default_random_engine generator(high_resolution_clock::now().time_since_epoch().count());
		vector<AI> newAI;
		// splice networks
		for (int i = 0; i < nSplice; i++) {
			// select mum and dad netorks to splice
			int mumIdx = randomIdx(generator);
			int dadIdx = randomIdx(generator);
			while (mumIdx == dadIdx) dadIdx = randomIdx(generator);
			// splice networks
			AI child = population[mumIdx] + population[dadIdx];
			child.generation = generation;
			newAI.push_back(child);
		}
		// evolve networks
		for (int i = 0; i < nEvolve; i++) {
			AI child = population[i].evolve();
			child.generation = generation;
			newAI.push_back(child);
		}
		// resize and add new AIs
		population.resize(halfIdx);
		population.insert(population.end(), newAI.begin(), newAI.end());

	}

	// Load from file
	//	loads the last saved generation
	void resume() {
		int populationSize;
		ifstream saveFile("Last_Save.data");
		saveFile >> generation >> populationSize;
		stringstream gen;
		gen << generation;
		ifstream AIFile("generation_" + gen.str() + ".data");
		for (int i = 0; i < populationSize; ++i) {
			AI inputAI;
			AIFile >> inputAI;
			population.push_back(inputAI);
		}
		saveGen = true;
	}

	// Save to file
	//	Saves the current generation to file
	void save() {
		ofstream AIFile("Last_Save.data");
		AIFile << generation << " " << population.size() << endl;
		AIFile.close();
		stringstream gen;
		gen << generation;
		AIFile.open("generation_" + gen.str() + ".data");
		for (AI& ai : population) {
			AIFile << ai << endl;
		}
		AIFile.close();
		saveGen = true;
	}
};


#endif // !Training_h
