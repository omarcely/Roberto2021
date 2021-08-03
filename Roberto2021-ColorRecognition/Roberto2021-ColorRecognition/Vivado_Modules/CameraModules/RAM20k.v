
module RAM20k(o_Data, i_Write_Adress, i_Read_Adress, i_Data, i_Enable_Read, i_Enable_Write, i_clk);

output reg [7:0] o_Data;
input [7:0] i_Data;
input [14:0] i_Write_Adress;
input [14:0] i_Read_Adress;
input i_Enable_Read, i_Enable_Write, i_clk;

reg [7:0] memory [20000:0];

  always @(negedge i_clk) begin
    if (i_Enable_Write) begin
      memory[i_Write_Adress] <= i_Data;
    end
    else begin
      memory[i_Write_Adress] <= memory[i_Write_Adress];
    end

    if (i_Enable_Read) begin
      o_Data <= memory[i_Read_Adress];
    end
    else begin
      o_Data <= o_Data;
    end
  end
endmodule
