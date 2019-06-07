// See README.md for license details.

package y86_64

import chisel3._


class CPU {

}


class ICache extends Module {
  val io = IO(new Bundle{
    val readAddress = Input(UInt(64.W))
    val readData = Output(UInt(64.W))
  })
}

class RegisterFile extends Module {
  val io = IO(new Bundle{
    val regA = Input(UInt(4.W))
    val regAEnable = Input(Bool())
    val regAData = Output(UInt(64.W))
    val regB = Input(UInt(4.W))
    val regBEnable = Input(Bool())
    val regBData = Output(UInt(64.W))
    val regM = Input(UInt(4.W))
    val regMEnable = Input(Bool())
    val regMData = Input(UInt(64.W))
    val regE = Input(UInt(4.W))
    val regEEnable = Input(Bool())
    val regEData = Input(UInt(64.W))
  })

  val mem = Mem(16, UInt(64.W))


  // write
  when (io.regMEnable) { mem(io.regM) := io.regMData }
  when (io.regEEnable) { mem(io.regE) := io.regEData }

  // read
  io.regAData := 0.U
  when (io.regAEnable) { io.regAData := mem(io.regA) }
  io.regBData := 0.U
  when (io.regBEnable) { io.regBData := mem(io.regB) }

}