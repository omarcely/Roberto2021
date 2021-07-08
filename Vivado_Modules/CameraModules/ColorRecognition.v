module ColorRecognition( o_color, o_RAM_adress,o_done,i_enable,i_RAMinfo,i_BytesPerFrame, i_clk);
input [7:0]i_RAMinfo;
input i_enable, i_clk;
input [14:0]i_BytesPerFrame;
output reg[7:0] o_color;
output reg[14:0] o_RAM_adress = 0;
output reg[0:0]o_done = 0;

reg [4:0] red, green, blue;
reg [1:0] green1;
reg [2:0] green2;
reg [10:0] r_totalRed = 0, r_totalGreen = 0, r_totalBlue = 0;
always@(posedge i_clk) begin
    if(i_enable == 1'b1)begin
        if(o_RAM_adress < i_BytesPerFrame)begin
            if(o_RAM_adress%2 == 0)begin
                red = i_RAMinfo[6:2];
                green1 = i_RAMinfo[1:0]; 
                o_RAM_adress <= o_RAM_adress +1;
            end else begin
                    green2 = i_RAMinfo[7:5];
                    blue = i_RAMinfo[4:0];
                    green = {green1,green2};
                    o_RAM_adress <= o_RAM_adress +1;
                    r_totalRed = r_totalRed + red;  
                    r_totalGreen = r_totalGreen + green;
                    r_totalBlue = r_totalBlue + blue;
                end
        end else begin
            o_RAM_adress <= 0;
            if(r_totalRed > r_totalGreen && r_totalRed > r_totalBlue)begin
                o_color = 8'b00000001;
                o_done = 1'b1;
            end
            if(r_totalGreen > r_totalRed && r_totalGreen > r_totalBlue)begin
                o_color = 8'b00000010;
                o_done = 1'b1;
            end
            if(r_totalBlue > r_totalGreen && r_totalBlue > r_totalRed)begin
                o_color = 8'b00000011;
                o_done = 1'b1;
            end
            if(r_totalRed + r_totalGreen > 3*r_totalBlue)begin
                o_color = 8'b00000100;
                o_done = 1'b1;
            end
        end
    end
end  

endmodule
