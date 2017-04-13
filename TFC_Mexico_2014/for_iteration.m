function BinaryData= for_iteration(Array,iteration,mean,offset)
    for i=1:iteration
        if(Array(i)<mean)
            BinaryData(i+offset)=0;
        else
            BinaryData(i+offset)=1;
        end
    end
end