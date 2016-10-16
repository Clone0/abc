package testb11;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.Random;

import weka.classifiers.Evaluation;
import weka.classifiers.bayes.NaiveBayes;
import weka.classifiers.trees.J48;
import weka.core.Instances;

public class B11 {
	public static void main(String[] args){
		try{
			BufferedReader br=new BufferedReader(new FileReader("test.arff"));
			Instances train=new Instances(br);
			train.setClassIndex(train.numAttributes()-1);
			
			NaiveBayes nB=new NaiveBayes();
			nB.buildClassifier(train);
			
			Evaluation eval=new Evaluation(train);
			eval.crossValidateModel(nB, train, 10,new Random(1));
			
			System.out.println("NAIVE BAYES CLASSIFICATION:-\n");
			System.out.println(eval.toSummaryString("RESULTS:-\n",true));
			System.out.println(eval.toMatrixString("CONFUSION MATRIX:-\n"));
			System.out.println(eval.toClassDetailsString("CLASS DETAILS:-\n"));
			
			BufferedReader brd=new BufferedReader(new FileReader("test.arff"));
			Instances test=new Instances(brd);
			test.setClassIndex(test.numAttributes()-1);
			
			J48 tree=new J48();
			tree.buildClassifier(test);
			tree.setOptions(null);
			
			Evaluation ev=new Evaluation(test);
			ev.evaluateModel(tree, test);
			
			System.out.println("====================================================================================================================\n");
			System.out.println("DECISION TREE:-\n");
			System.out.println(ev.toSummaryString("RESULTS:-\n",true));
			System.out.println(ev.toMatrixString("CONFUSION MATRIX:-\n"));
			System.out.println(ev.toClassDetailsString("CLASS DETAILS:-\n"));
			
		}
		catch(Exception e){
			e.printStackTrace();
		}
	}

}
