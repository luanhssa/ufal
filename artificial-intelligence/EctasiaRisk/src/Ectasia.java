import java.io.BufferedReader;
import java.io.FileReader;
import java.util.Random;

import weka.classifiers.Classifier;
import weka.classifiers.Evaluation;
import weka.classifiers.functions.RBFNetwork;
import weka.core.Instances;
import weka.filters.Filter;
import weka.filters.unsupervised.attribute.Remove;
import weka.filters.unsupervised.attribute.Standardize;


public class Ectasia {

	Instances data = null;

	public static void main(String[] args) {
		String dataset = "data/Risco de Ectasia x Topo (alunos)ed.arff";
		Ectasia ec = new Ectasia(dataset);

		ec.removeFilter(createRemoveOptions(1));
		ec.standardizeFilter();
		
		ec.applyRBFNClassifier(createRBFNOptions(2, 160, "1.0E-8", -1, 0.1), 100, 1);
	}

	private static String[] createRemoveOptions(int index) {
		String[] options = new String[2];
		options[0] = "-R";
		options[1] = String.valueOf(index);
		return options;
	}

	public Ectasia(String dataset) {
		try {
			data = readDataSet(dataset);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public Instances readDataSet(String dataset) throws Exception {
		BufferedReader reader = new BufferedReader(new FileReader(dataset));
		Instances data = new Instances(reader);
		reader.close();

		data.setClassIndex(data.numAttributes() -1);
		return data;
	}

	public void removeFilter(String[] options) {
		Remove remove = new Remove();
		try {
			remove.setOptions(options);
			remove.setInputFormat(data);

			data = Filter.useFilter(data, remove);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public void standardizeFilter() {
		Standardize standardize = new Standardize();
		try {
			standardize.setInputFormat(data);

			data = Filter.useFilter(data, standardize);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private static String[] createRBFNOptions(int clusters, int clusterSeeds, String ridge, int maxIts, double minStdDev) {
		String[] options = new String[10];
		options[0] = "-B";
		options[1] = String.valueOf(clusters);
		options[2] = "-S";
		options[3] = String.valueOf(clusterSeeds);
		options[4] = "-R";
		options[5] = ridge;
		options[6] = "-M";
		options[7] = String.valueOf(maxIts);
		options[8] = "-W";
		options[9] = String.valueOf(minStdDev);
		return options;
	}
	
	private void applyRBFNClassifier(String[] options, int folds, int seed) {
		RBFNetwork rbf = new RBFNetwork();
		try {
			rbf.setOptions(options);
			
			crossValidate(rbf, folds, seed);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	public void crossValidationStratified(Classifier cls, int folds, int runs) throws Exception {
		for (int i = 0; i < runs; i++) {
			int seed = i + 1;
			Random rand = new Random(seed);
			Instances randData = new Instances(data);
			randData.randomize(rand);
			if (randData.classAttribute().isNominal())
				randData.stratify(folds);

			Evaluation eval = new Evaluation(randData);
			for (int n = 0; n < folds; n++) {
				Instances train = randData.trainCV(folds, n);
				Instances test = randData.testCV(folds, n);

				Classifier clsCopy = Classifier.makeCopy(cls);
				clsCopy.buildClassifier(train);
				eval.evaluateModel(clsCopy, test);
			}

			printEvaluation(cls, folds, seed, eval);
		}
	}

	public void crossValidate(Classifier cls, int folds, int seed) throws Exception {

		cls.buildClassifier(data);
		Evaluation eval = new Evaluation(data);

		eval.crossValidateModel(cls, data, folds, new Random(seed));

		printEvaluation(cls, folds, seed, eval);
	}

	public void printEvaluation(Classifier cls, int folds, int seed, Evaluation eval) throws Exception {
		System.out.println();
		System.out.println("=== Setup run ===");
		System.out.println("Classifier: " + cls.getClass().getName());
		System.out.println("Dataset: " + data.relationName());
		System.out.println("Folds: " + folds);
//		System.out.println("Seed: " + seed);
		System.out.println();
		System.out.println(cls);
		System.out.println();
		System.out.println(eval.toSummaryString("=== " + folds + "-fold Cross-validation ===", true));
		System.out.println(eval.toClassDetailsString());
		System.out.println(eval.toMatrixString());
	}
}
