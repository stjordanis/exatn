/** ExaTN: Tensor basic types and parameters
REVISION: 2020/04/19

Copyright (C) 2018-2020 Dmitry I. Lyakh (Liakh)
Copyright (C) 2018-2020 Oak Ridge National Laboratory (UT-Battelle) **/

#ifndef EXATN_NUMERICS_TENSOR_BASIC_HPP_
#define EXATN_NUMERICS_TENSOR_BASIC_HPP_

#include <cstdint>

namespace exatn{

using Int4 = int32_t;
using Int8 = int64_t;
using UInt4 = uint32_t;
using UInt8 = uint64_t;

using SpaceId = unsigned int;              //space id type
using SubspaceId = unsigned long long int; //subspace id type
using SymmetryId = int;                    //symmetry id type
using DimExtent = unsigned long long int;  //dimension extent type
using DimOffset = unsigned long long int;  //dimension base offset type

using ScopeId = unsigned int; //TAProL scope ID type

constexpr DimExtent MAX_SPACE_DIM = 0xFFFFFFFFFFFFFFFF; //max dimension of unregistered (anonymous) spaces
constexpr SpaceId SOME_SPACE = 0; //any unregistered (anonymous) space (all registered spaces will have SpaceId > 0)
constexpr SubspaceId FULL_SUBSPACE = 0; //every space has its trivial (full) subspace automatically registered as subspace 0
constexpr SubspaceId UNREG_SUBSPACE = 0xFFFFFFFFFFFFFFFF; //id of any unregistered subspace

enum class LegDirection{
 UNDIRECT, //no direction
 INWARD,   //inward direction
 OUTWARD   //outward direction
};

enum class TensorOpCode{
 NOOP,              //no operation
 CREATE,            //tensor creation
 DESTROY,           //tensor destruction
 TRANSFORM,         //tensor transformation/initialization
 SLICE,             //tensor slicing
 INSERT,            //tensor insertion
 ADD,               //tensor addition
 CONTRACT,          //tensor contraction
 DECOMPOSE_SVD3,    //tensor decomposition via SVD into three tensor factors
 DECOMPOSE_SVD2,    //tensor decomposition via SVD into two tensor factors
 ORTHOGONALIZE_SVD, //tensor orthogonalization via SVD
 ORTHOGONALIZE_MGS, //tensor orthogonalization via Modified Gram-Schmidt
 BROADCAST,         //tensor broadcast (parallel execution only)
 ALLREDUCE          //tensor allreduce (parallel execution only)
};

enum class TensorElementType{
 VOID,
 REAL16,
 REAL32,
 REAL64,
 COMPLEX16,
 COMPLEX32,
 COMPLEX64
};

template <TensorElementType> constexpr std::size_t TensorElementTypeSize();
template <> constexpr std::size_t TensorElementTypeSize<TensorElementType::VOID>(){return 0;} //0 bytes
template <> constexpr std::size_t TensorElementTypeSize<TensorElementType::REAL16>(){return 2;} //2 bytes
template <> constexpr std::size_t TensorElementTypeSize<TensorElementType::REAL32>(){return 4;} //4 bytes
template <> constexpr std::size_t TensorElementTypeSize<TensorElementType::REAL64>(){return 8;} //8 bytes
template <> constexpr std::size_t TensorElementTypeSize<TensorElementType::COMPLEX16>(){return 4;} //4 bytes
template <> constexpr std::size_t TensorElementTypeSize<TensorElementType::COMPLEX32>(){return 8;} //8 bytes
template <> constexpr std::size_t TensorElementTypeSize<TensorElementType::COMPLEX64>(){return 16;} //16 bytes

} //namespace exatn

#endif //EXATN_NUMERICS_TENSOR_BASIC_HPP_
