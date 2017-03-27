package com.kit.indornavigation.core.algos;

import java.util.ArrayDeque;
import java.util.Deque;

public final class MovingAverage implements FilteringAlgorithm {

    private final Deque<Double> dataArray;
    private final int window;

    public MovingAverage(int window) {
        dataArray = new ArrayDeque<>(window);
        this.window = window;
    }

    @Override
    public double filter(double data) {
        if (dataArray.size() == window) {
            dataArray.pollFirst();
        }

        dataArray.addLast(data);

        double sum = 0;

        for (double d : dataArray) {
            sum += d;
        }

        return sum / dataArray.size();
    }


}
