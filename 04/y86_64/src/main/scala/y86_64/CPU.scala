// See README.md for license details.

package y86_64

import chisel3._
import chisel3.util._


class CPU {

}

class Instruction extends Bundle {
  val icode :: halt :: nop :: rrmovq :: irmovq :: rmmovq
    :: mrmovq :: opq :: jxx :: cmovxx :: call :: ret :: pusq :: popq = Enum(13)
  val ifun :: addq :: subq :: andq :: xorq :: jmp :: jle ::jl :: je :: jne :: jge :: jg = Enum(2)
}

class Decoder extends Module {
}

class ICache extends Module {
  val io = IO(new Bundle {
    val readAddress = Input(UInt(64.W))
    val readData = Output(UInt((8 * 10).W))
  })
  io.readData := 0.U
  //  val mem = Mem(1024, UInt(8.W))
  //  val tmp = 0.U
  //  for (i <- 0 to 10) {
  ////    io.readData(8 * (i + 1) - 1, 8 * i) := mem(io.readAddress + i.U)
  //  }
}

class RegisterFile extends Module {
  val io = IO(new Bundle {
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
  when(io.regMEnable) {
    mem(io.regM) := io.regMData
  }
  when(io.regEEnable) {
    mem(io.regE) := io.regEData
  }

  // read
  io.regAData := 0.U
  when(io.regAEnable) {
    io.regAData := mem(io.regA)
  }
  io.regBData := 0.U
  when(io.regBEnable) {
    io.regBData := mem(io.regB)
  }

}