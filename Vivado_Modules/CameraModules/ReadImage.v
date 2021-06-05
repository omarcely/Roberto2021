
module ReadImage(o_XLK, o_to_RAM, o_RAM_Adress, o_RAM_Write_Enable, i_D, i_PLK, i_Clk, i_VS, i_HS);

input [7:0]i_D;
output o_XLK;
output reg [7:0]o_to_RAM;
output reg [14:0]o_RAM_Adress;
output reg [0:0]o_RAM_Write_Enable;
input i_PLK, i_Clk, i_VS, i_HS;  

reg [2:0]s_Clock_Count = 0;
reg s_Clock_Value = 1;
reg [14:0]s_Current_Register = 0;/////    Usar para saber si ya se termin[o de leer toda la info de un frame (9215 = 9216-1)

assign o_XLK = s_Clock_Value;

    always @(posedge i_Clk) 
    begin
        if (s_Clock_Count <4) 
        begin
        s_Clock_Count <= s_Clock_Count +1;
        end
        else
        begin
        s_Clock_Count <=0;
        s_Clock_Value <= ~s_Clock_Value;
        end    
    end
      
    always @(posedge i_PLK)
    begin
        if(i_VS == 1'b0) begin
            if (i_HS == 1'b1) begin
                o_RAM_Write_Enable = 1'b1;  
                o_RAM_Adress = s_Current_Register;
                o_to_RAM = i_D;
                s_Current_Register = s_Current_Register+1;
            end
            else begin
                o_RAM_Write_Enable = 1'b0;
            end
        end
        else begin
             s_Current_Register = 0;
        end
    end   
    
    
endmodule
