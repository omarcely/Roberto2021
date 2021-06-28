
module Main(o_Tx, o_Frame_Indicator, o_led, o_XLK, i_D,  i_PLK, Clk, i_VS, i_HS, i_RX);

input [7:0]i_D;
output o_XLK, o_Tx;
output reg o_Frame_Indicator;
output [1:0]o_led;
input i_PLK, Clk, i_VS, i_HS, i_RX;

///////Define finite states
localparam Waiting = 2'b00;
localparam WaitBeforeSending = 2'b01;
localparam SendingBytes = 2'b10;
localparam WaitAfterSending = 2'b11;

////Define Number of Bytes
localparam ClockCountsPerBit = 1085;
localparam ClockCountsPerByte = 62510;//1250010;   ////Eleven times the number of Clock Counts Per Bit (10 for the bytes an one wxtra for the microcontroller to detect the change of Byte)
localparam BytesPerFrame = 6144;
localparam ClockCountsForControlSignal = 125000;

wire [7:0] w_RAM_Input;
wire [7:0] w_RAM_Output;
wire [14:0] w_Write_Adress;
wire w_Enable_Write;


reg r_Enable_Tx = 0;
reg [14:0] r_Read_Adress = 0;
reg [20:0] r_Current_Clock_Count = 0;    /////// [14:0]

reg [1:0]r_Current_State = WaitAfterSending;
reg [1:0]r_Next_State = WaitAfterSending;
reg VS_Current_Value = 1'b0;
reg VS_Previous_Value = 1'b0;
reg r_EnableCameraRead = 1'b1;


RAM20k RAM (w_RAM_Output,
            w_Write_Adress,
            r_Read_Adress,
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
              w_RAM_Output,
              o_led[0],
              o_Tx,
              o_led[1]);

assign VS_Posedge = VS_Current_Value & (~VS_Previous_Value);
assign VS_Negedge = (~VS_Current_Value) & (VS_Previous_Value);


  always @(posedge Clk) begin

    VS_Current_Value <= i_VS;
    VS_Previous_Value <=  VS_Current_Value;

    case(r_Current_State)
      Waiting: begin
        r_Enable_Tx <= 1'b0;
        r_Read_Adress <= 0;
        r_EnableCameraRead <= 1'b1;

        if(VS_Posedge==0)begin
          r_Next_State <= Waiting;
          r_Current_Clock_Count <= 1'b0;
          o_Frame_Indicator <= 1'b1;
          r_EnableCameraRead <= 1'b1;
        end
        else begin
          r_Next_State <= WaitBeforeSending;
          r_Current_Clock_Count <= 1'b0;
          o_Frame_Indicator <= 1'b0;
          r_EnableCameraRead <= 1'b0;
        end

      end ///End of Waiting




      WaitBeforeSending: begin
        r_Enable_Tx <= 1'b0;
        r_Read_Adress <= 0;
        r_EnableCameraRead <= 1'b0;

        if (r_Current_Clock_Count < ClockCountsForControlSignal) begin
          r_Current_Clock_Count <= r_Current_Clock_Count + 1;
          r_Next_State = WaitBeforeSending;
          o_Frame_Indicator <= 1'b0;
        end else begin
          r_Current_Clock_Count <= 1'b0;
          r_Next_State <= SendingBytes;
          o_Frame_Indicator <= 1'b0;
        end
      end ///End of WaitBeforeSending




      SendingBytes: begin
        o_Frame_Indicator <= 1'b0;
        r_EnableCameraRead <= 1'b0;

        if(r_Current_Clock_Count <  ClockCountsPerBit) begin
          r_Current_Clock_Count <= r_Current_Clock_Count + 1;
          r_Enable_Tx <= 1'b1;
          r_Next_State <= SendingBytes;
          r_Read_Adress <= r_Read_Adress;
        end
        else begin
          if (r_Current_Clock_Count <  ClockCountsPerByte) begin
            r_Current_Clock_Count <= r_Current_Clock_Count + 1;
            r_Enable_Tx <= 1'b0;
            r_Next_State <= SendingBytes;
            r_Read_Adress <= r_Read_Adress;
          end else begin
            if (r_Read_Adress < BytesPerFrame -1) begin
              r_Current_Clock_Count <= 0;
              r_Enable_Tx <= 1'b0;
              r_Next_State <= SendingBytes;
              r_Read_Adress <= r_Read_Adress + 1;
            end else begin
              r_Current_Clock_Count <= 0;
              r_Enable_Tx <= 1'b0;
              r_Next_State <= WaitAfterSending;
              r_Read_Adress <= 0;
            end

          end
        end
      end  ///End of SendingBytes



      WaitAfterSending: begin
        r_Enable_Tx <= 1'b0;
        r_Read_Adress <= 0;
        r_EnableCameraRead <= 1'b0;
        r_Current_Clock_Count <= 1'b0;

        if (VS_Negedge == 1'b0) begin
          r_Next_State <= WaitAfterSending;
          o_Frame_Indicator <= 1'b0;
        end else begin
          r_Next_State <= Waiting;
          o_Frame_Indicator <= 1'b0;
        end
      end ///End of WaitAfterSending

    endcase
  end

  always @(negedge Clk) begin
        r_Current_State <= r_Next_State;
  end


endmodule
