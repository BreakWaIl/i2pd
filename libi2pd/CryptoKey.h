#ifndef CRYPTO_KEY_H__
#define CRYPTO_KEY_H__

#include <inttypes.h>
#include "Crypto.h"

namespace i2p
{
namespace crypto
{
	class CryptoKeyEncryptor 
	{
		public:

			virtual ~CryptoKeyEncryptor () {};
			virtual void Encrypt (const uint8_t * data, uint8_t * encrypted, BN_CTX * ctx) = 0; // 222 bytes data, 512 bytes encrypted
	};	

	class CryptoKeyDecryptor 
	{
		public:

			virtual ~CryptoKeyDecryptor () {};
			virtual bool Decrypt (const uint8_t * encrypted, uint8_t * data, BN_CTX * ctx) = 0; // 512 bytes encrypted, 222 bytes data
	};

	class ElGamalEncryptor: public CryptoKeyEncryptor // for destination
	{
		public:

			ElGamalEncryptor (const uint8_t * pub);
			void Encrypt (const uint8_t * data, uint8_t * encrypted, BN_CTX * ctx); 

		private:

			uint8_t m_PublicKey[256];
	};

	class ElGamalDecryptor: public CryptoKeyDecryptor // for destination
	{
		public:

			ElGamalDecryptor (const uint8_t * priv);
			bool Decrypt (const uint8_t * encrypted, uint8_t * data, BN_CTX * ctx); 

		private:

			uint8_t m_PrivateKey[256];
	};

	class ECIESP256Encryptor: public CryptoKeyEncryptor 
	{
		public:

			ECIESP256Encryptor (const uint8_t * pub);
			~ECIESP256Encryptor ();
			void Encrypt (const uint8_t * data, uint8_t * encrypted, BN_CTX * ctx); 

		private:

			EC_GROUP * m_Curve;
			EC_POINT * m_PublicKey;
	};


	class ECIESP256Decryptor: public CryptoKeyDecryptor
	{
		public:

			ECIESP256Decryptor (const uint8_t * priv);
			~ECIESP256Decryptor ();
			bool Decrypt (const uint8_t * encrypted, uint8_t * data, BN_CTX * ctx); 

		private:

			EC_GROUP * m_Curve;
			BIGNUM * m_PrivateKey;
	};

	void CreateECIESP256RandomKeys (uint8_t * priv, uint8_t * pub);
}
}

#endif

