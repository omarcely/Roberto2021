
module ColorRecognition( o_color, o_RAM_adress,o_done,i_enable,i_RAMinfo,i_BytesPerFrame, i_clk);
input [7:0]i_RAMinfo;
input [0:0]i_enable, i_clk;
input [14:0]i_BytesPerFrame;
output reg[7:0] o_color = 8'b11110000;
output reg[14:0] o_RAM_adress = 0;
output reg[0:0]o_done = 1'b0;


reg [4:0] red=0, green=0, blue=0;
reg [1:0] green1=0;
reg [2:0] green2=0;
reg [14:0] r_totalRed = 0, r_totalGreen = 0, r_totalBlue = 0,r_totalWhite =0;
reg [7:0] FrameInfo;


assign enableMod = i_enable;

always@(negedge i_clk) begin
    FrameInfo <= i_RAMinfo;
    if(enableMod == 1'b1)begin
        o_done = 1'b0;
        if(o_RAM_adress < i_BytesPerFrame)begin
            if(o_RAM_adress % 2 == 0)begin
                red <= FrameInfo[6:2];
                green1 <= FrameInfo[1:0]; 
                o_RAM_adress = o_RAM_adress +1;
            end else begin
                    green2 <= FrameInfo[7:5];
                    blue <= FrameInfo[4:0];
                    green = {green1,green2};
                    o_RAM_adress = o_RAM_adress +1;
                    o_color <= 8'b100; 
                    if((red > green) & (red > blue))begin
                        r_totalRed = r_totalRed + 1;
                    end else begin
                        if((green > red) & (green > blue))begin
                            r_totalGreen = r_totalGreen + 1;                   
                        end else begin
                            if((blue > green) & (blue > red))begin
                                r_totalBlue = r_totalBlue + 1;
                            end else begin
                                r_totalWhite = r_totalWhite + 1;
                            end
                        end
                    end
                end
        end else begin
            o_RAM_adress = 0;
            if(r_totalWhite > 3000)begin
            o_color <= 8'b00000100;
            end else begin
                if((r_totalRed > r_totalGreen) & (r_totalRed > r_totalBlue))begin
                    o_color <= 8'b00000001;
                end 
                if(((r_totalGreen-72) > r_totalRed) & ((r_totalGreen-72)> r_totalBlue))begin
                    o_color <= 8'b00000010;
                end
                if((r_totalBlue > r_totalGreen) & (r_totalBlue > r_totalRed))begin
                    o_color <= 8'b00000011;
                end
            end
            o_done = 1'b1;
            r_totalRed = 0;
            r_totalGreen = 0;
            r_totalBlue = 0;
            r_totalWhite = 0; 
            red = 0;
            green1 = 0;
            green2 = 0;
            green = 0;
            blue = 0; 
        end
    end
end  

endmodule
