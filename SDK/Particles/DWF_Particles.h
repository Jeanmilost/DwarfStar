/****************************************************************************
 * ==> DWF_Particles -------------------------------------------------------*
 ****************************************************************************
 * Description: Particles system                                            *
 * Developer:   Jean-Milost Reymond                                         *
 ****************************************************************************
 * MIT License - DwarfStar Game Engine                                      *
 *                                                                          *
 * Permission is hereby granted, free of charge, to any person obtaining a  *
 * copy of this software and associated documentation files (the            *
 * "Software"), to deal in the Software without restriction, including      *
 * without limitation the rights to use, copy, modify, merge, publish,      *
 * distribute, sub-license, and/or sell copies of the Software, and to      *
 * permit persons to whom the Software is furnished to do so, subject to    *
 * the following conditions:                                                *
 *                                                                          *
 * The above copyright notice and this permission notice shall be included  *
 * in all copies or substantial portions of the Software.                   *
 *                                                                          *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  *
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   *
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY     *
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,     *
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE        *
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                   *
 ****************************************************************************/

#pragma once

// std
#include <vector>

// classes
#include "DWF_Particle.h"
#include "DWF_Box.h"
#include "DWF_Model.h"

namespace DWF_Particles
{
    /**
    * Particles system
    *@author Jean-Milost Reymond
    */
    class Particles
    {
        public:
            DWF_Geometry::Box m_Area; // area which will contain the particles

            /**
            * Called when a texture should be loaded
            *@param arg1 - texture name to load
            *@param arg2 - if true, the texture is a 32 bit texture
            *@return the loaded texture
            *@note The loaded texture will be deleted internally, and should no longer be deleted from outside
            */
            typedef std::function<void(Particles*, Particle*, double)> ITfOnCalculateMotion;

            Particles();
            virtual ~Particles();

            /**
            * Gets the model
            *@return the model
            */
            virtual inline DWF_Model::Model* GetModel() const;

            /**
            * Sets the model
            *@param pModel - the model to set
            */
            virtual inline void SetModel(const std::shared_ptr<DWF_Model::Model>& pModel);

            /**
            * Adds a particle
            *@return the newly added particle
            */
            virtual Particle* Add();

            /**
            * Adds particles
            *@param count - number of particles to add
            */
            virtual void Add(std::size_t count);

            /**
            * Deletes a particle
            *@param pParticle - particle to delete
            */
            virtual void Delete(Particle* pParticle);

            /**
            * Deletes a particle at index
            *@param index - particle index to delete
            */
            virtual void DeleteAt(std::size_t index);

            /**
            * Gets a particle at index
            *@param index - particle index to get
            *@return particle at index
            */
            virtual Particle* Get(std::size_t index) const;

            /**
            * Gets the particle count
            *@return the particle count
            */
            virtual std::size_t GetCount() const;

            /**
            * Animates the particles
            *@param elapsedTime - elapsed time since last frame
            */
            virtual void Animate(double elapsedTime);

            /**
            * Sets the OnCalculateMotion callback
            *@param fOnCalculateMotion - callback function handle
            */
            void Set_OnCalculateMotion(ITfOnCalculateMotion fOnCalculateMotion);

        private:
            typedef std::vector<Particle*> IParticles;

            std::shared_ptr<DWF_Model::Model> m_pModel;
            IParticles                        m_Particles;
            ITfOnCalculateMotion              m_fOnCalculateMotion = nullptr;
    };

    //---------------------------------------------------------------------------
    // Particles
    //---------------------------------------------------------------------------
    inline DWF_Model::Model* Particles::GetModel() const
    {
        return m_pModel.get();
    }
    //---------------------------------------------------------------------------
    inline void Particles::SetModel(const std::shared_ptr<DWF_Model::Model>& pModel)
    {
        m_pModel = pModel;
    }
    //---------------------------------------------------------------------------
}
