function result = kalm(in_x, in_t)
    persistent lastT X P;
    global isInit;
    if (~isInit)
        isInit = true;
        result = in_x;
        lastT = in_t;
        X = [ in_x ; 0];
        P = [100 0 ; 0 100];
        result = in_x;
        return;
    end
    
    Q = [0.001 0 ; 0 0.001];
    
    A = [1 , in_t - lastT ; 0 , 1];
    
    % predict
    
    predX = A * X;
    predP = A * P * A.' + Q;
    
    % Kalman gain
    
    R = 0.1;  
    K = predP * [1;0] / (predP(1,1)+R);
   
    % correct
    
    X = predX + K * (in_x - predX(1));
    P = (eye(2) - K*[1 0])*predP;
    
    result = X(1);
    lastT = in_t;
    
end