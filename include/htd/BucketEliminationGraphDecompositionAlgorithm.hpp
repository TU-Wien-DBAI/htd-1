/* 
 * File:   BucketEliminationGraphDecompositionAlgorithm.hpp
 * 
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015-2016, Michael Abseher
 *    E-Mail: <abseher@dbai.tuwien.ac.at>
 * 
 * This file is part of htd.
 * 
 * htd is free software: you can redistribute it and/or modify it under 
 * the terms of the GNU General Public License as published by the Free 
 * Software Foundation, either version 3 of the License, or (at your 
 * option) any later version.
 * 
 * htd is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public 
 * License for more details.

 * You should have received a copy of the GNU General Public License
 * along with htd.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef HTD_HTD_BUCKETELIMINATIONGRAPHDECOMPOSITIONALGORITHM_HPP
#define	HTD_HTD_BUCKETELIMINATIONGRAPHDECOMPOSITIONALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/IGraphDecompositionAlgorithm.hpp>

#include <htd/ILabelingFunction.hpp>
#include <htd/IMutableGraphDecomposition.hpp>
#include <htd/IGraphDecompositionManipulationOperation.hpp>

#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>

namespace htd
{
    /**
     *  Default implementation of the IGraphDecompositionAlgorithm interface based on bucket elimination.
     */
    class BucketEliminationGraphDecompositionAlgorithm : public virtual htd::IGraphDecompositionAlgorithm
    {
        public:
            /**
             *  Constructor for a graph decomposition algorithm based on bucket elimination.
             */
            BucketEliminationGraphDecompositionAlgorithm(void);

            /**
             *  Constructor for a graph decomposition algorithm based on bucket elimination.
             *
             *  @note When calling this method the control over the memory regions of the manipulation operations is transferred to the
             *  decomposition algorithm. Deleting a manipulation operation provided to this method outside the decomposition algorithm
             *  or assigning the same manipulation operation multiple times will lead to undefined behavior.
             *
             *  @param[in] manipulationOperations   The manipulation operations which shall be applied globally to each decomposition generated by the algorithm.
             */
            BucketEliminationGraphDecompositionAlgorithm(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations);

            ~BucketEliminationGraphDecompositionAlgorithm();
            
            htd::IGraphDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph) const HTD_OVERRIDE;

            htd::IGraphDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const HTD_OVERRIDE;

            /**
             *  Compute a decomposition of the given graph and apply the given manipulation operations to it. The manipulation operations are applied in the given order.
             *
             *  @param[in] graph                        The input graph to decompose.
             *  @param[in] manipulationOperationCount   The number of manipulation operations which are provided to this function.
             *
             *  @note The manipulation operations provided to this function are applied right after the manipulation operations defined globally for the algorithm.
             *
             *  @note When calling this method the control over the memory regions of the manipulation operations is transferred to the
             *  decomposition algorithm. Deleting a manipulation operation provided to this method outside the decomposition algorithm
             *  or assigning the same manipulation operation multiple times will lead to undefined behavior.
             *
             *  @return A new IGraphDecomposition object representing the decomposition of the given graph.
             */
            htd::IGraphDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph, int manipulationOperationCount, ...) const;

            void setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) HTD_OVERRIDE;

            void addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation) HTD_OVERRIDE;

            void addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) HTD_OVERRIDE;

            bool isSafelyInterruptible(void) const HTD_OVERRIDE;

            BucketEliminationGraphDecompositionAlgorithm * clone(void) const HTD_OVERRIDE;

        protected:
            /**
             *  Copy assignment operator for a graph decomposition algorithm based on bucket elimination.
             *
             *  @note This operator is protected to prevent assignments to an already initialized algorithm.
             */
            BucketEliminationGraphDecompositionAlgorithm & operator=(const BucketEliminationGraphDecompositionAlgorithm &) { return *this; }

        private:
            std::vector<htd::ILabelingFunction *> labelingFunctions_;

            std::vector<htd::IGraphDecompositionManipulationOperation *> postProcessingOperations_;

            htd::IMutableGraphDecomposition * computeMutableDecomposition(const htd::IMultiHypergraph & graph) const;

            htd::vertex_t getMinimumVertex(const std::vector<htd::vertex_t> & vertices, const std::unordered_map<htd::vertex_t, htd::index_t> & vertexIndices) const;

            htd::vertex_t getMinimumVertex(const std::vector<htd::vertex_t> & vertices, const std::unordered_map<htd::vertex_t, htd::index_t> & vertexIndices, htd::vertex_t excludedVertex) const;

            void distributeEdge(htd::index_t edgeIndex, const std::vector<htd::vertex_t> & edge, htd::vertex_t startBucket, const std::unordered_map<htd::vertex_t, std::vector<htd::vertex_t>> & buckets, const std::unordered_map<htd::vertex_t, std::vector<htd::vertex_t>> & neighbors, std::unordered_map<htd::vertex_t, std::vector<htd::index_t>> & inducedEdges, std::vector<htd::id_t> & lastAssignedEdge, std::stack<htd::vertex_t> & originStack) const;
    };
}

#endif /* HTD_HTD_BUCKETELIMINATIONGRAPHDECOMPOSITIONALGORITHM_HPP */
