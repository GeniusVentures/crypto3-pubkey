//---------------------------------------------------------------------------//
// Copyright (c) 2018-2020 Mikhail Komarov <nemo@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef CRYPTO3_PUBKEY_ENCRYPT_HPP
#define CRYPTO3_PUBKEY_ENCRYPT_HPP

#include <nil/crypto3/pubkey/cipher_value.hpp>
#include <nil/crypto3/pubkey/cipher_state.hpp>

namespace nil {
    namespace crypto3 {
        /*!
         * @brief
         *
         * @ingroup block_algorithms
         *
         * @tparam PublicKeyCipher
         * @tparam InputIterator
         * @tparam KeyIterator
         * @tparam OutputIterator
         *
         * @param first
         * @param last
         * @param key_first
         * @param key_last
         * @param out
         *
         * @return
         */
        template<typename PublicKeyCipher, typename InputIterator, typename KeyIterator, typename OutputIterator>
        OutputIterator encrypt(InputIterator first, InputIterator last, KeyIterator key_first, KeyIterator key_last,
                               OutputIterator out) {

            typedef typename PublicKeyCipher::stream_encrypter_type EncryptionMode;
            typedef typename pubkey::accumulator_set<EncryptionMode> CipherAccumulator;

            typedef pubkey::detail::value_cipher_impl<CipherAccumulator> StreamEncrypterImpl;
            typedef pubkey::detail::itr_cipher_impl<StreamEncrypterImpl, OutputIterator> EncrypterImpl;

            return EncrypterImpl(first, last, std::move(out), CiperState(PublicKeyCipher(key_first, key_last)));
        }

        /*!
         * @brief
         *
         * @ingroup block_algorithms
         *
         * @tparam PublicKeyCipher
         * @tparam InputIterator
         * @tparam OutputAccumulator
         *
         * @param first
         * @param last
         * @param acc
         *
         * @return
         */
        template<typename PublicKeyCipher, typename InputIterator,
                 typename OutputAccumulator =
                     typename pubkey::accumulator_set<typename PublicKeyCipher::stream_encrypter_type>>
        OutputAccumulator &encrypt(InputIterator first, InputIterator last, OutputAccumulator &acc) {

            typedef pubkey::detail::ref_cipher_impl<OutputAccumulator> StreamEncrypterImpl;
            typedef pubkey::detail::range_cipher_impl<StreamEncrypterImpl> EncrypterImpl;

            return EncrypterImpl(first, last, acc);
        }

        /*!
         * @brief
         *
         * @ingroup block_algorithms
         *
         * @tparam PublicKeyCipher
         * @tparam SinglePassRange
         * @tparam OutputAccumulator
         *
         * @param r
         * @param acc
         *
         * @return
         */
        template<typename PublicKeyCipher, typename SinglePassRange,
                 typename OutputAccumulator =
                     typename pubkey::accumulator_set<typename PublicKeyCipher::stream_encrypter_type>>
        OutputAccumulator &encrypt(const SinglePassRange &r, OutputAccumulator &acc) {

            typedef pubkey::detail::ref_cipher_impl<OutputAccumulator> StreamEncrypterImpl;
            typedef pubkey::detail::range_cipher_impl<StreamEncrypterImpl> EncrypterImpl;

            return EncrypterImpl(r, acc);
        }

        /*!
         * @brief
         *
         * @ingroup block_algorithms
         *
         * @tparam PublicKeyCipher
         * @tparam InputIterator
         * @tparam KeyIterator
         * @tparam CipherAccumulator
         *
         * @param first
         * @param last
         * @param key_first
         * @param key_last
         *
         * @return
         */
        template<typename PublicKeyCipher, typename InputIterator, typename KeyIterator,
                 typename CipherAccumulator =
                     typename pubkey::accumulator_set<typename PublicKeyCipher::stream_encrypter_type>>
        pubkey::detail::range_cipher_impl<pubkey::detail::value_cipher_impl<CipherAccumulator>>
            encrypt(InputIterator first, InputIterator last, KeyIterator key_first, KeyIterator key_last) {

            typedef pubkey::detail::value_cipher_impl<CipherAccumulator> StreamEncrypterImpl;
            typedef pubkey::detail::range_cipher_impl<StreamEncrypterImpl> EncrypterImpl;

            return EncrypterImpl(first, last, CipherAccumulator(PublicKeyCipher(key_first, key_last)));
        }

        /*!
         * @brief
         *
         * @ingroup block_algorithms
         *
         * @tparam PublicKeyCipher
         * @tparam SinglePassRange
         * @tparam KeyRange
         * @tparam OutputIterator
         *
         * @param rng
         * @param key
         * @param out
         *
         * @return
         */
        template<typename PublicKeyCipher, typename SinglePassRange, typename KeyRange, typename OutputIterator>
        OutputIterator encrypt(const SinglePassRange &rng, const KeyRange &key, OutputIterator out) {

            typedef typename PublicKeyCipher::stream_encrypter_type EncryptionMode;
            typedef typename pubkey::accumulator_set<EncryptionMode> CipherAccumulator;

            typedef pubkey::detail::value_cipher_impl<CipherAccumulator> StreamEncrypterImpl;
            typedef pubkey::detail::itr_cipher_impl<StreamEncrypterImpl, OutputIterator> EncrypterImpl;

            return EncrypterImpl(rng, std::move(out), CipherState(PublicKeyCipher(key)));
        }

        /*!
         * @brief
         *
         * @ingroup block_algorithms
         *
         * @tparam PublicKeyCipher
         * @tparam SinglePassRange
         * @tparam KeyRange
         * @tparam CipherAccumulator
         *
         * @param r
         * @param key
         *
         * @return
         */
        template<typename PublicKeyCipher, typename SinglePassRange, typename KeyRange,
                 typename CipherAccumulator =
                     typename pubkey::accumulator_set<typename PublicKeyCipher::stream_encrypter_type>>
        pubkey::detail::range_cipher_impl<pubkey::detail::value_cipher_impl<CipherAccumulator>>
            encrypt(const SinglePassRange &r, const KeyRange &key) {

            typedef pubkey::detail::value_cipher_impl<CipherAccumulator> StreamEncrypterImpl;
            typedef pubkey::detail::range_cipher_impl<StreamEncrypterImpl> EncrypterImpl;

            return EncrypterImpl(r, CipherState(PublicKeyCipher(key)));
        }
    }    // namespace crypto3
}    // namespace nil

#endif    // include guard