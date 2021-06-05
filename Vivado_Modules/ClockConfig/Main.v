
module Boruto(
        input Clk,
        output reg pija
    );
    
    reg [2:0]conteo = 3'b0;
    
    always @(posedge Clk) 
    begin
        if (conteo <3'b101) 
        begin
        conteo <= conteo +1;
        end
        else
        begin
        conteo <=3'b0;
        pija <= ~pija;
        end
    
    end
endmodule
