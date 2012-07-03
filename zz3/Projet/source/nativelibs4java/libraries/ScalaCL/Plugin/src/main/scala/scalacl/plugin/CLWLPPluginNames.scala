package com.nativelibs4java.scalaxy ; package common
import pluginBase._

import tools.nsc.Global
import reflect.NameTransformer
;
trait CLWLPPluginNames extends PluginNames {
  import global._
  import definitions._
  import treeInfo.{ methPart }
  import typer.typed

  val ScalaCLPackage       = M("scalaclWLP")
  val ScalaCLPackageClass  = ScalaCLPackage.tpe.typeSymbol
  val CLDataIOClass = C("scalaclWLP.impl.CLDataIO")
  val CLArrayClass = C("scalaclWLP.CLArray")
  val CLFunctionClass = C("scalaclWLP.impl.CLFunction")
  val CLRangeClass = C("scalaclWLP.CLRange")
  val CLCollectionClass = C("scalaclWLP.CLCollection")
  val CLFilteredArrayClass = C("scalaclWLP.CLFilteredArray")
  val scalacl_ = N("scalacl")
  val getCachedFunctionName = N("getWLPCachedFunction")
  val Function2CLFunctionName = N("Function2CLFunction")
  val withCaptureName = N("withCapture")
}
