module Main(o_Tx, i_Frame_Indicator, o_led, o_XLK,o_led_state,i_D,  i_PLK, Clk, i_VS, i_HS);

input [7:0]i_D;
output o_XLK, o_Tx;
output [1:0]o_led;
output reg [1:0]o_led_state=2'b00;
input i_PLK, Clk, i_VS, i_HS, i_Frame_Indicator;

///////Define finite states
localparam WaitForCapture = 2'b00;
localparam LoadIntoRAM = 2'b01;
localparam Recognition = 2'b10;
localparam SendingInfo = 2'b11;

localparam BytesPerFrame = 11376;//6144;

wire [7:0] w_RAM_Input;
wire [7:0] w_RAM_Output;
wire [14:0] w_Write_Adress;
wire [14:0] w_Read_Adress;
wire w_Enable_Write;
wire w_Enable_Read;
wire [0:0]w_recognition_done;
wire [7:0]w_colorOfFrame;


reg r_Enable_Tx = 0;
reg [1:0]r_Current_State = WaitForCapture;
reg [1:0]r_Next_State = WaitForCapture;
reg VS_Current_Value = 1'b0;
reg VS_Previous_Value = 1'b0;
reg FI_Current_Value = 1'b0;
reg FI_Previous_Value = 1'b0;
reg r_EnableCameraRead = 1'b0;
reg [0:0]r_EnableRecognition = 1'b0;
reg availableForFrame = 1'b0;
reg [2:0]r_count_for_sending = 1'b0;

RAM20k RAM (w_RAM_Output,
            w_Write_Adress,
            w_Read_Adress,
            w_RAM_Input,
            1'b1,
            w_Enable_Write,
            Clk);

ReadImage Image (o_XLK,
                 w_RAM_Input,
                 w_Write_Adress,
                 w_Enable_Write,
                 i_D,
                 i_PLK,
                 Clk,
                 i_VS,
                 i_HS,
                 r_EnableCameraRead);

Tx Transmiter(Clk,
              r_Enable_Tx,
              w_colorOfFrame,
              o_led[0],
              o_Tx,
              o_led[1]);

ColorRecognition Color(w_colorOfFrame,
                       w_Read_Adress,
                       w_recognition_done,
                       r_EnableRecognition,
                       w_RAM_Output,
                       BytesPerFrame, 
                       Clk);

assign VS_Posedge = VS_Current_Value & (~VS_Previous_Value);
assign VS_Negedge = (~VS_Current_Value) & (VS_Previous_Value);
assign FI_Posedge = FI_Current_Value & (~FI_Previous_Value);
assign FI_Negedge = (~FI_Current_Value) & FI_Previous_Value;

  always @(posedge Clk) begin

    VS_Current_Value <= i_VS;
    VS_Previous_Value <=  VS_Current_Value;
    FI_Current_Value <= i_Frame_Indicator;
    FI_Previous_Value <= FI_Current_Value;
    
    case(r_Current_State)
    
      LoadIntoRAM: begin
        r_Enable_Tx <= 1'b0;
        r_EnableCameraRead <= 1'b1;
        r_EnableRecognition <= 1'b0;
        availableForFrame <= 1'b0;
        o_led_state[0] <= 1'b1;
        o_led_state[1] <= 1'b0;
        if(VS_Posedge==0)begin
          r_Next_State <= LoadIntoRAM;
          r_EnableCameraRead <= 1'b1;
        end
        else begin
          r_Next_State <= Recognition;
          r_EnableCameraRead <= 1'b0;
        end
      end 


      Recognition: begin
        r_Enable_Tx <= 1'b0;
        r_EnableCameraRead <= 1'b0;
        r_EnableRecognition <= 1'b1;
        o_led_state[0] <= 1'b0;
        o_led_state[1] <= 1'b1;
        if(w_recognition_done == 1'b1)begin
            r_Next_State <= SendingInfo;
        end else begin
            r_Next_State <= Recognition;
            end
      end 


      SendingInfo: begin
        r_EnableCameraRead <= 1'b0;
        r_EnableRecognition <= 1'b0;
        r_Enable_Tx <= 1'b1;
        o_led_state[0] <= 1'b1;
        o_led_state[1] <= 1'b1;
        if(r_count_for_sending == 3'd5)begin
            r_Next_State <= WaitForCapture;
            r_count_for_sending <= 0;
        end else begin
                r_count_for_sending <= r_count_for_sending +1;
            end
      end  


      WaitForCapture: begin
        r_Enable_Tx <= 1'b0;
        r_EnableCameraRead <= 1'b0;
        r_EnableRecognition <= 1'b0;
        o_led_state[0] <= 1'b0;
        o_led_state[1] <= 1'b0;
        if(FI_Posedge == 1'b1)begin
            availableForFrame = 1'b1;
        end 
        if (VS_Negedge == 1'b1 & availableForFrame == 1'b1) begin
          r_Next_State <= LoadIntoRAM;
        end else begin
          r_Next_State <= WaitForCapture;
        end
      end 
    endcase
  end

  always @(negedge Clk) begin
        r_Current_State <= r_Next_State;
  end


endmodule
