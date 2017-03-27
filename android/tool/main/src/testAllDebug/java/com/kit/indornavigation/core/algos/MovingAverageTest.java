package com.kit.indornavigation.core.algos;

import junit.framework.TestCase;

import org.junit.Test;

import java.util.Arrays;

public class MovingAverageTest {

    @Test
    public void testBelowWindow() throws Exception {
        FilteringAlgorithm algorithm = new MovingAverage(5);

        double[] result = new double[3];

        for (int i = 0; i < result.length; i++) {
            result[i] = algorithm.filter(i + 1);
        }

        TestCase.assertEquals(Arrays.toString(result), Arrays.toString(new double[]{1, 1.5, 2}));
    }

    @Test
    public void testOneValue() throws Exception {
        FilteringAlgorithm algorithm = new MovingAverage(30);

        double expected = 12.21301203;
        TestCase.assertEquals(expected, algorithm.filter(expected));
    }

    @Test
    public void testNormal() throws Exception {
        FilteringAlgorithm algorithm = new MovingAverage(5);

        double[] result = new double[11];

        for (int i = 0; i < result.length; i++) {
            result[i] = algorithm.filter(i + 1);
        }

        TestCase.assertEquals(Arrays.toString(new double[]{1, 1.5, 2, 2.5, 3, 4, 5, 6, 7, 8, 9}), Arrays.toString(result));
    }

    @Test
    public void testNegative() throws Exception {
        FilteringAlgorithm algorithm = new MovingAverage(5);

        double[] result = new double[11];

        for (int i = 0; i < result.length; i++) {
            result[i] = algorithm.filter((i + 1) * -1);
        }

        TestCase.assertEquals(Arrays.toString(new double[]{-1, -1.5, -2, -2.5, -3, -4, -5, -6, -7, -8, -9}), Arrays.toString(result));
    }
}