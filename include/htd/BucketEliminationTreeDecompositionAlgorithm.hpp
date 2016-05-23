/* 
 * File:   BucketEliminationTreeDecompositionAlgorithm.hpp
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

#ifndef HTD_HTD_BUCKETELIMINATIONTREEDECOMPOSITIONALGORITHM_HPP
#define	HTD_HTD_BUCKETELIMINATIONTREEDECOMPOSITIONALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/ITreeDecompositionAlgorithm.hpp>

#include <htd/ILabelingFunction.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/ITreeDecompositionManipulationOperation.hpp>

#include <vector>
#include <unordered_set>

namespace htd
{
    /**
     *  Default implementation of the ITreeDecompositionAlgorithm interface based on bucket elimination.
     */
    class BucketEliminationTreeDecompositionAlgorithm : public virtual htd::ITreeDecompositionAlgorithm
    {
        public:
            /**
             *  Constructor for a tree decomposition algorithm based on bucket elimination.
             */
            BucketEliminationTreeDecompositionAlgorithm(void);

            /**
             *  Constructor for a tree decomposition algorithm based on bucket elimination.
             *
             *  @note When calling this method the control over the memory regions of the manipulation operations is transferred to the
             *  decomposition algorithm. Deleting a manipulation operation provided to this method outside the decomposition algorithm
             *  or assigning the same manipulation operation multiple times will lead to undefined behavior.
             *
             *  @param[in] manipulationOperations   The manipulation operations which shall be applied globally to each decomposition generated by the algorithm.
             */
            BucketEliminationTreeDecompositionAlgorithm(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations);

            ~BucketEliminationTreeDecompositionAlgorithm();
            
            htd::ITreeDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph) const HTD_OVERRIDE;

            htd::ITreeDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const HTD_OVERRIDE;

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
             *  @return A new ITreeDecomposition object representing the decomposition of the given graph.
             */
            htd::ITreeDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph, int manipulationOperationCount, ...) const;

            void setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) HTD_OVERRIDE;

            void addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation) HTD_OVERRIDE;

            void addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) HTD_OVERRIDE;

            BucketEliminationTreeDecompositionAlgorithm * clone(void) const HTD_OVERRIDE;

        protected:
            /**
             *  Copy assignment operator for a tree decomposition algorithm based on bucket elimination.
             *
             *  @note This operator is protected to prevent assignments to an already initialized algorithm.
             */
            BucketEliminationTreeDecompositionAlgorithm & operator=(const BucketEliminationTreeDecompositionAlgorithm &) { return *this; }

        private:
            std::vector<htd::ILabelingFunction *> labelingFunctions_;

            std::vector<htd::ITreeDecompositionManipulationOperation *> postProcessingOperations_;

            htd::IMutableTreeDecomposition * computeMutableDecomposition(const htd::IMultiHypergraph & graph) const;
    };
}

#endif /* HTD_HTD_BUCKETELIMINATIONTREEDECOMPOSITIONALGORITHM_HPP */
